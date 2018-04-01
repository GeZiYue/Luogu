#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
priority_queue<string,vector<string>,greater<string> >p;
string a[100005];
string b;
int main(){
    int n,m,i;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    cin>>b;
    m=b.size();
    for(i=1;i<=n;i++){
        if(a[i].substr(0,m)==b){
            p.push(a[i]);
        }
    }
    while(!p.empty()){
        cout<<p.top()<<endl;
        p.pop();
    }
    return 0;
}
