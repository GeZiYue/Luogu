#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
    int n,a,b,i,ans=0;
    cin>>n;
    cin>>a;
    ans=a;
    for(i=2;i<=n;i++){
        cin>>b;
        if(b>a){
            ans+=(b-a);
        }
        a=b;
    }
    cout<<ans<<endl;
}
