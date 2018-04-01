#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<list>
using namespace std;
#define Int(a) read(a)
void add(int n,int m);
int dp(int n);
void read(int &r_e_a_d);
int a[16005];
list<int> b[16005];
bool vis[16005];
int maxans;
int main(){
    int n,i,l1,l2;
    Int(n);
    for(i=1;i<=n;i++){
        Int(a[i]);
    }
    for(i=1;i<n;i++){
        Int(l1);
        Int(l2);
        add(l1,l2);
        add(l2,l1);
    }
    vis[1]=1;
    dp(1);
    cout<<maxans<<endl;
    return 0;
}
void add(int n,int m){
    b[n].push_back(m);
}
int dp(int n){
    int ans=a[n],l,m;
    list<int>::iterator each;
    for(each=b[n].begin();each!=b[n].end();each++){
    	l=(*each);
        if(vis[l]==0){
            vis[l]=1;
            ans+=max(dp(l),0);
        }
    }
    maxans=max(maxans,ans);
    return ans;
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
