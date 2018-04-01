#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
#define lc(n) (n<<1)
#define rc(n) (n<<1|1)
#define ll unsigned long long int
ll maxn[320005];
ll a[40005],b[40005],h[40005];
ll ha[120005],c[120005];
map<ll,ll>has;
template<class T>void read(T &r_e_a_d);
void update(int n,int nL,int nR,int uL,int uR,ll num);
ll query(int n,int L,int R);
int main(){
    int n,m=0,k=0,i;
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
        read(b[i]);
        b[i]--;
        read(h[i]);
        ha[++m]=a[i];
        ha[++m]=b[i];
        ha[++m]=a[i]-1;
    }
    sort(ha+1,ha+m+1);
    for(i=1;i<=m;i++){
        if(ha[i]!=ha[i-1]){
            c[++k]=ha[i]-ha[i-1];
            has[ha[i]]=k;
        }
    }
    for(i=1;i<=n;i++){
        update(1,1,k,has[a[i]],has[b[i]],h[i]);
    }
    cout<<query(1,1,k)<<endl;
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
    maxn[lc(n)]=max(maxn[lc(n)],maxn[n]);
    maxn[rc(n)]=max(maxn[rc(n)],maxn[n]);
}
void update(int n,int nL,int nR,int uL,int uR,ll num){
    if(nL==uL&&nR==uR){
        if(num>=maxn[n]){
            maxn[n]=num;
        }
        return;
    }
    down(n);
    int M=(nL+nR)>>1;
    if(M>=uR){
        update(lc(n),nL,M,uL,uR,num);
    }else{
        if(M<uL){
            update(rc(n),M+1,nR,uL,uR,num);
        }else{
            update(lc(n),nL,M,uL,M,num);
            update(rc(n),M+1,nR,M+1,uR,num);
        }
    }
}
ll query(int n,int L,int R){
    if(L==R){
        return c[L]*maxn[n];
    }
    down(n);
    int M=(L+R)>>1;
    return query(lc(n),L,M)+query(rc(n),M+1,R);
}
