#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define n 30000
#define N 30005
template<class T1>void read(T1 &r_e_a_d);
int find(int x);
void merge(int x,int y);
int query(int x,int y);
int fa[N],num[N],sum[N];
int main(){
    int m,i,x,y;
    char ch;
    read(m);
    for(i=1;i<=n;i++){
        fa[i]=i;
        sum[i]=1;
        num[i]=0;
    }
    for(i=1;i<=m;i++){
        cin>>ch;
        read(x);
        read(y);
        if(ch=='M'){
            merge(x,y);
        }else{
            printf("%d\n",query(x,y));
        }
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
int find(int x){
    if(fa[x]==x){
        return x;
    }
    int father=find(fa[x]);
    num[x]+=num[fa[x]];
    return fa[x]=father;
}
void merge(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        num[fy]+=sum[fx];
        sum[fx]+=sum[fy];
        sum[fy]=0;
        fa[fy]=fx;
    }
}
int query(int x,int y){
    int fx=find(x),fy=find(y);
    if(fx!=fy){
        return -1;
    }else{
        return abs(num[x]-num[y])-1;
    }
}
