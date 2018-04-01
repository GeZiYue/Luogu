#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define N 105
#define M 10005
int a[M];
int dis[N][N];
#define isNum(a) (a>='0'&&a<='9')
template<class T1>void read(T1 &r_e_a_d);
int main(){
    int n,m,i,j,k,ans=0;
    read(n);
    read(m);
    for(i=1;i<=m;i++){
        read(a[i]);
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            read(dis[i][j]);
        }
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(j==i){
                continue;
            }
            for(k=1;k<=n;k++){
                if(k==i||k==j){
                    continue;
                }
                dis[j][k]=min(dis[j][k],dis[j][i]+dis[i][k]);
            }
        }
    }
    for(i=2;i<=m;i++){
        ans+=dis[a[i-1]][a[i]];
    }
    cout<<ans<<endl;
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
