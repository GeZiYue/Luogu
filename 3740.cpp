#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
#define ll unsigned long long int
#define N 10000000
int cn[1600005];
int m=1;
int L[1600005],R[1600005];
int a[10005],b[10005];
bool ans[10005];
template<class T>void read(T &r_e_a_d);
void update(int n,int nL,int nR,int uL,int uR,int num);
void query(int n,int qL,int qR);
int main(){
    int n,k,i,sum=0;
    read(k);
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
        read(b[i]);
        update(1,1,N,a[i],b[i],i);
    }
    query(1,1,N);
    for(i=1;i<=n;i++){
        if(ans[i]){
            sum++;
        }
    }
    cout<<sum<<endl;
    return 0;
}
template<class T>
void read(T &r_e_a_d){
    T k=0;
    bool flag=0;
    char c;
    while(1){
        c=getchar();
        if(c=='-'){
            flag=1;
            break;
        }
        if(c>='0'&&c<='9'){
            k=c-'0';
            break;
        }
    }
    while(1){
        c=getchar();
        if(c<'0'||c>'9'){
            break;
        }else{
            k=(k<<1)+(k<<3)+c-'0';
        }
    }
    if(flag==1){
        k=-k;
    }
    r_e_a_d=k;
}
void down(int n){
    if(cn[n]!=0){
        if(L[n]==0){
            L[n]=++m;
        }
        if(R[n]==0){
            R[n]=++m;
        }
        cn[L[n]]=cn[n];
        cn[R[n]]=cn[n];
        cn[n]=0;
    }
}
void update(int n,int nL,int nR,int uL,int uR,int num){
    if(nL>=uL&&nR<=uR){
        cn[n]=num;
        return;
    }
    if(nR<uL||nL>uR){
        return;
    }
    down(n);
    int M=(nL+nR)>>1;
    if(L[n]==0){
        L[n]=++m;
    }
    if(R[n]==0){
        R[n]=++m;
    }
    update(L[n],nL,M,uL,uR,num);
    update(R[n],M+1,nR,uL,uR,num);
}
void query(int n,int qL,int qR){
    if(cn[n]){
        ans[cn[n]]=1;
        return;
    }
    if(qL==qR){
        return;
    }
    down(n);
    int M=(qL+qR)>>1;
    if(L[n]!=0){
        query(L[n],qL,M);
    }
    if(R[n]!=0){
        query(R[n],M+1,qR);
    }
}
