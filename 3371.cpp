#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
#define N 10005
#define M 500005
#define isNum(a) (a>='0'&&a<='9')
int hed[N],nxt[2*M],to[2*M],diss[2*M];
int id;
int dis[N];
queue<int>que;
bool flag[N];
template<class T1>void read(T1 &r_e_a_d);
void add(int x,int y,int z);
int main(){
    int n,m,begin,now,i,a,b,c;
    read(n);
    read(m);
    read(begin);
    for(i=1;i<=m;i++){
        read(a);
        read(b);
        read(c);
        add(a,b,c);
    }
    for(i=1;i<=n;i++){
        dis[i]=2147483647;
    }
    dis[begin]=0;
    flag[begin]=1;
    que.push(begin);
    while(!que.empty()){
        now=que.front();
        que.pop();
        i=hed[now];
        flag[now]=0;
        while(i){
            if(dis[now]+diss[i]<dis[to[i]]){
                dis[to[i]]=dis[now]+diss[i];
                if(flag[to[i]]==0){
                    que.push(to[i]);
                    flag[to[i]]=1;
                }
            }
            i=nxt[i];
        }
    }
    for(i=1;i<=n;i++){
        cout<<dis[i]<<' ';
    }
    cout<<endl;
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
void add(int x,int y,int z){
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    diss[id]=z;
}
