#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
using namespace std;
struct Node{
    int num;
    int time;
}a[1005];
bool cmp(Node i,Node j);
int main(){
    long long n,sum=0,i;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i].time;
        a[i].num=i;
    }
    sort(a+1,a+n+1,cmp);
    for(i=1;i<=n;i++){
        cout<<a[i].num<<' ';
        sum+=a[i].time*(n-i);
    }
    cout<<endl<<fixed<<setprecision(2)<<(1.0*sum/n)<<endl;
}
bool cmp(Node i,Node j){
    if(i.time==j.time){
        return i.num<j.num;
    }else{
        return i.time<j.time;
    }
}
