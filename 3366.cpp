#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
void read(int &r_e_a_d);
struct K{
    int begin;
    int end;
    int cost;
}a[200005];
bool cmp(K i,K j);
int up(int i);
bool check(int i,int j);
void merge(int i,int j);
int t[5005];
int main(){
    int n,m,i,j,ans=0,sum=0;
    Int(n);Int(m);
    for(i=1;i<=n;i++){
        t[i]=i;
    }
    for(i=1;i<=m;i++){
        Int(a[i].begin);Int(a[i].end);Int(a[i].cost);
    }
    sort(a+1,a+m+1,cmp);
    for(i=1;i<=m;i++){
        if(check(a[i].begin,a[i].end)==0){
            sum++;
            ans+=a[i].cost;
            merge(a[i].begin,a[i].end);
            if(sum==n-1){
                goto success;
            }
        }
    }
    cout<<"orz"<<endl;
    success:cout<<ans<<endl;
    return 0;
}
bool cmp(K i,K j){
    return i.cost<j.cost;
}
int up(int i){
    if(t[i]==i){
        return i;
    }else{
        return t[i]=up(t[i]);
    }
}
bool check(int i,int j){
    return up(i)==up(j);
}
void merge(int i,int j){
    int x=up(i),y=up(j);
    t[y]=x;
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
