#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define N 200000
#define ll long long int
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
ll maxn[(N<<2)+5];
ll Mod;
ll Tree_Query(int x,int xL,int xR,int qL,int qR);
void Tree_Update(int x,int xL,int xR,int uL,int uR,ll num);
int main(){
    int n,i,len=0;
    ll a,t=0;
    char ch;
    read(n);
    read(Mod);
    for(i=1;i<=n;i++){
        cin>>ch;
        cin>>a;
        if(ch=='A'){
            len++;
            Tree_Update(1,1,N,len,len,(a+t)%Mod);
        }else{
            if(len==0){
                write(0);
                EL;
                continue;
            }
            write(t=Tree_Query(1,1,N,len-a+1,len));
            EL;
        }
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        if(ch=='-'){
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch)){
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
template<class T1>void write(T1 w_r_i_t_e){
    if(w_r_i_t_e<0){
        putchar('-');
        write(-w_r_i_t_e);
    }else{
        if(w_r_i_t_e<10){
            putchar(w_r_i_t_e+'0');
        }else{
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
ll Tree_Query(int x,int xL,int xR,int qL,int qR){
    if(xL>=qL&&xR<=qR){
        return maxn[x];
    }
    if(xR<qL||xL>qR){
        return 0;
    }
    int M=(xL+xR)>>1;
    return max(Tree_Query(ls(x),xL,M,qL,qR),Tree_Query(rs(x),M+1,xR,qL,qR));
}
void Tree_Update(int x,int xL,int xR,int uL,int uR,ll num){
    if(xR<uL||xL>uR){
        return;
    }
    if(xL==xR){
        maxn[x]=num;
        return;
    }
    int M=(xL+xR)>>1;
    Tree_Update(ls(x),xL,M,uL,uR,num);
    Tree_Update(rs(x),M+1,xR,uL,uR,num);
    maxn[x]=max(maxn[ls(x)],maxn[rs(x)]);
}
