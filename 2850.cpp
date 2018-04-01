#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 5005
#define M 100005
#define isNum(a) (a>='0'&&a<='9')
int be[M],to[M],diss[M];
int id;
int dis[N];
template<class T1>void read(T1 &r_e_a_d);
void add(int x,int y,int z);
int main(){
    int t;
    int n,m,k,i,j,a,b,c;
    bool flag;
    read(t);
    while(t--){
        read(n);
        read(m);
        read(k);
        id=0;
        for(i=1;i<=m;i++){
            read(a);
            read(b);
            read(c);
            add(a,b,c);
            add(b,a,c);
        }
        for(i=1;i<=k;i++){
            read(a);
            read(b);
            read(c);
            add(a,b,-c);
        }
        memset(dis,10,sizeof(dis));
        dis[1]=0;
        for(i=1;i<=n;i++){
            flag=0;
            for(j=1;j<=id;j++){
                if(dis[be[j]]+diss[j]<dis[to[j]]){
                    dis[to[j]]=dis[be[j]]+diss[j];
                    flag=1;
                }
            }
            if(flag==0){
                cout<<"NO"<<endl;
                goto back;
            }
        }
        cout<<"YES"<<endl;
        back:;
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
void add(int x,int y,int z){
    be[++id]=x;
    to[id]=y;
    diss[id]=z;
}
