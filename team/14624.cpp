#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<vector>
#include<queue>
using namespace std;
typedef unsigned long long int ll;
struct cmp1{  
     bool operator()(ll x,ll y){  
        return x>y;
    }  
};
priority_queue<ll,vector<ll>,cmp1>a;
int main(){
    ll n,i,sum=0,ans=0,x,y,l;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>l;
        a.push(l);
        sum+=l;
    }
    for(i=2;i<=n;i++){
        x=a.top();
        a.pop();
        y=a.top();
        a.pop();
        ans+=x+y;
        a.push(x+y);
    }
    cout<<sum<<' '<<ans<<endl;
}

