#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
bool cmp(string a,string b){
    return a+b>b+a;
}
int main(){
    int n,i;
    string a[25];
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    sort(a+1,a+n+1,cmp);
    for(i=1;i<=n;i++){
        cout<<a[i];
    }
    return 0;
}

