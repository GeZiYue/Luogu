#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
using namespace std;
#define N 10000005
#define M 1000005
#define isNum(a) (a>='0'&&a<='9')
bool is[N];
int prime[M];
int id=0;
template<class T1>void read(T1 &r_e_a_d);
void makeprime(int n);
int main(){
    int i,n,m,a;
    read(n);
    read(m);
    makeprime(n);
    for(i=1;i<=m;i++){
        read(a);
        if(is[a]){
            puts("No");
        }else{
            puts("Yes");
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
void makeprime(int n){
    int i,j;
    is[1]=1;
    for(i=2;i<=n;i++){
        if(!is[i]){
            prime[++id]=i;
        }
        for(j=1;j<=id&&i*prime[j]<=n;j++){
            is[i*prime[j]]=1;
            if(i%prime[j]==0){
                break;
            }
        }
    }
}
