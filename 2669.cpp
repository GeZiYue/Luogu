#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
    int n,i,sum=0;
    cin>>n;
    for(i=1;i<=n;i++){
        sum+=i*i;
        n-=i;
    }
    sum+=n*i;
    cout<<sum<<endl;
}
