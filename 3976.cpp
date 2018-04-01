#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
using namespace std;
#define N 50005
#define ls(n) (n<<1)
#define rs(n) (n<<1|1)
#define gswap(x,y) (x^=y^=x^=y)
#define mid(x,y) ((x+y)>>1)
#define inf 2147483647
#define isNum(a) (a>='0'&&a<='9')
int hed[N],nxt[2*N],to[2*N];
int dep[N],siz[N],son[N],fa[N],top[N],go[N],back[N];
int maxn[4*N],minn[4*N],ansn[4*N],tag[4*N];
int value[N];
int id1,id2;
int n;
template<class T1>void read(T1 &r_e_a_d);
void add(int x,int y);
void DFS1(int x);
void DFS2(int x);
void Tree_Build(int x,int xL,int xR);
void Tree_Push_Down(int x);
void Tree_Push_Up(int x);
void Tree_Update(int x,int xL,int xR,int uL,int uR,int num);
int Tree_Query(int x,int xL,int xR,int uL,int uR);
int Tree_Query_Max(int x,int xL,int xR,int uL,int uR);
int Tree_Query_Min(int x,int xL,int xR,int uL,int uR);
void Fin_Update(int x,int y,int num);
int Fin_Query(int x,int y);
int Get_Answer(int x,int y,int num);
int main(){
    int m,i,a,b,v;
    read(n);
    for(i=1;i<=n;i++){
        read(value[i]);
    }
    for(i=1;i<n;i++){
        read(a);
        read(b);
        add(a,b);
        add(b,a);
    }
    DFS1(1);
    top[1]=1;
    DFS2(1);
    Tree_Build(1,1,n);
    read(m);
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        read(v);
        printf("%d\n",Get_Answer(a,b,v));
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        ch=getchar();
        if(ch=='-'){
            flag=-1;
        }
    }
    while(isNum(ch)){
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
void add(int x,int y){
    nxt[++id1]=hed[x];
    hed[x]=id1;
    to[id1]=y;
}
void DFS1(int x){
    siz[x]=1;
    dep[x]=dep[fa[x]]+1;
    for(int i=hed[x];i;i=nxt[i]){
        if(fa[x]!=to[i]){
            fa[to[i]]=x;
            DFS1(to[i]);
            siz[x]+=siz[to[i]];
            if(son[x]==0||siz[to[i]]>siz[son[x]]){
                son[x]=to[i];
            }
        }
    }
}
void DFS2(int x){
    go[x]=++id2;
    back[id2]=value[x];
    if(son[x]){
        top[son[x]]=top[x];
        DFS2(son[x]);
    }
    for(int i=hed[x];i;i=nxt[i]){
        if(fa[x]!=to[i]&&son[x]!=to[i]){
            top[to[i]]=to[i];
            DFS2(to[i]);
        }
    }
}
void Tree_Build(int x,int xL,int xR){
    if(xL==xR){
        maxn[x]=minn[x]=back[xL];
    }else{
        int M=mid(xL,xR);
        Tree_Build(ls(x),xL,M);
        Tree_Build(rs(x),M+1,xR);
        Tree_Push_Up(x);
    }
}
void Tree_Push_Down(int x){
    maxn[ls(x)]+=tag[x];
    minn[ls(x)]+=tag[x];
    tag[ls(x)]+=tag[x];
    maxn[rs(x)]+=tag[x];
    minn[rs(x)]+=tag[x];
    tag[rs(x)]+=tag[x];
    tag[x]=0;
}
void Tree_Push_Up(int x){
    maxn[x]=max(maxn[ls(x)],maxn[rs(x)]);
    minn[x]=min(minn[ls(x)],minn[rs(x)]);
    ansn[x]=max(max(ansn[ls(x)],ansn[rs(x)]),maxn[rs(x)]-minn[ls(x)]);
}
void Tree_Update(int x,int xL,int xR,int uL,int uR,int num){
    if(xL>=uL&&xR<=uR){
        maxn[x]+=num;
        minn[x]+=num;
        tag[x]+=num;
    }else{
        if(xR>=uL&&xL<=uR){
            Tree_Push_Down(x);
            int M=mid(xL,xR);
            Tree_Update(ls(x),xL,M,uL,uR,num);
            Tree_Update(rs(x),M+1,xR,uL,uR,num);
            Tree_Push_Up(x);
        }
    }
}
int Tree_Query(int x,int xL,int xR,int uL,int uR){
    if(xL>=uL&&xR<=uR){
        return ansn[x];
    }else{
        if(xR>=uL&&xL<=uR){
            Tree_Push_Down(x);
            int M=mid(xL,xR);
            return max(Tree_Query(ls(x),xL,M,uL,uR),Tree_Query(rs(x),M+1,xR,uL,uR));
        }else{
            return -inf;
        }
    }
}
int Tree_Query_Max(int x,int xL,int xR,int uL,int uR){
    if(xL>=uL&&xR<=uR){
        return maxn[x];
    }else{
        if(xR>=uL&&xL<=uR){
            Tree_Push_Down(x);
            int M=mid(xL,xR);
            return max(Tree_Query_Max(ls(x),xL,M,uL,uR),Tree_Query_Max(rs(x),M+1,xR,uL,uR));
        }else{
            return -inf;
        }
    }
}
int Tree_Query_Min(int x,int xL,int xR,int uL,int uR){
    if(xL>=uL&&xR<=uR){
        return minn[x];
    }else{
        if(xR>=uL&&xL<=uR){
            Tree_Push_Down(x);
            int M=mid(xL,xR);
            return max(Tree_Query_Min(ls(x),xL,M,uL,uR),Tree_Query_Min(rs(x),M+1,xR,uL,uR));
        }else{
            return inf;
        }
    }
}
void Fin_Update(int x,int y,int num){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            gswap(x,y);
        }
        Tree_Update(1,1,n,go[top[x]],go[x],num);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
        gswap(x,y);
    }
    Tree_Update(1,1,n,go[x],go[y],num);
}
int Fin_Query(int x,int y){
    int Ans=-inf;
    int Util_Min=inf;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]]){
            gswap(x,y);
        }
        Ans=max(Ans,Tree_Query(1,1,n,go[top[x]],go[x]));
        Ans=max(Ans,Tree_Query_Max(1,1,n,go[top[x]],go[x])-Util_Min);
        Util_Min=min(Util_Min,Tree_Query_Min(1,1,n,go[top[x]],go[x]));
        cout<<Tree_Query(1,1,n,go[top[x]],go[x])<<endl;
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]){
        gswap(x,y);
    }
    Ans=max(Ans,Tree_Query(1,1,n,go[x],go[y]));
    Ans=max(Ans,Tree_Query_Max(1,1,n,go[top[x]],go[x])-Util_Min);
    return Ans;
}
int Get_Answer(int x,int y,int num){
    Fin_Update(x,y,num);
    return Fin_Query(x,y);
}
