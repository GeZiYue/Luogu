#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
#define ll unsigned long long int
void read(int &r_e_a_d);
struct Cow{
    int be;
    int af;
    bool flag;
}a[50005];
bool cmp1(Cow i,Cow j){
    return i.af<j.af;
}
bool cmp2(Cow i,Cow j){
    return i.be<j.be;
}
int main(){
    int n,k,i,ans=0;
    ll m;
    Int(n);
    Int(k);
    cin>>m;
    for(i=1;i<=n;i++){
        Int(a[i].be);
        Int(a[i].af);
        a[i].flag=0;
    }
    sort(a+1,a+n+1,cmp1);
    for(i=1;i<=k;i++){
        if(m>=a[i].af){
            m-=a[i].af;
            a[i].flag=1;
            ans++;
        }else{
            break;
        }
    }
    sort(a+1,a+n+1,cmp2);
    for(i=1;i<=n;i++){
        if(m>=a[i].be){
            if(a[i].flag==0){
                m-=a[i].be;
                ans++;
            }
        }else{
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}
void read(int &r_e_a_d){
    int k=0;
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
