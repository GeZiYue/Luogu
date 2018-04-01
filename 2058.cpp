#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
void read(int &r_e_a_d);
int t[100005];
struct Node{
    int t;
    int x;
}a[300005];
int main(){
    int n,ti,k,now=0,i,j;
    int head=1,tail=0;
    Int(n);
    for(i=1;i<=n;i++){
        Int(ti);
        Int(k);
        for(j=1;j<=k;j++){
            a[++tail].t=ti;
            Int(a[tail].x);
            t[a[tail].x]++;
            if(t[a[tail].x]==1){
                now++;
            }
        }
        while(a[tail].t-a[head].t>=86400){
            if(t[a[head].x]==1){
                now--;
            }
            t[a[head].x]--;
            head++;
        }
        cout<<now<<endl;
    }
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
