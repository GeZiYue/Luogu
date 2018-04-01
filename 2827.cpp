#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<queue>
using namespace std;
int f[100005];
void read(int &a){
    char c;
    int ans;
    while(1){
        c=getchar();
        if(c>='0'&&c<='9'){
            ans=c-'0';
            break;
        }
    }
    while(1){
        c=getchar();
        if(c<'0'||c>'9'){
            break;
        }
        ans=(ans<<1)+(ans<<3)+c-'0';
    }
    a=ans;
}
queue<int>a,b,c;
int main(){
    int n,m,q,x,y,t,i,k,maxi,now;
    unsigned long long l;
    read(n);
    read(m);
    read(q);
    read(x);
    read(y);
    read(t);
    for(i=1;i<=n;i++){
        read(f[i]);
    }
    sort(f+1,f+n+1);
    for(i=n;i>=1;i--){
        a.push(f[i]);
    }
    for(i=1;i<=m;i++){
        maxi=-2147483647;
        now=0;
        if(a.front()>maxi&&!a.empty()){
            maxi=a.front();
            now=1;
        }
        if(b.front()>maxi&&!b.empty()){
            maxi=b.front();
            now=2;
        }
        if(c.front()>maxi&&!c.empty()){
            maxi=c.front();
            now=3;
        }
        maxi+=q*(i-1);
        if(now==1){
            a.pop();
        }else{
            if(now==2){
                b.pop();
            }else{
                c.pop();
            }
        }
        if(i%t==0){
            printf("%d ",maxi);
        }
        l=1ll*maxi*x/y;
        b.push(l-(1ll*q)*(1ll*i));
        c.push((1ll*maxi)-l-(1ll*q)*(1ll*i));
    }
    printf("\n");
    for(i=1;i<=(n+m);i++){
        maxi=-2147483647;
        now=0;
        if(a.front()>maxi&&(!a.empty())){
            maxi=a.front();
            now=1;
        }
        if(b.front()>maxi&&(!b.empty())){
            maxi=b.front();
            now=2;
        }
        if(c.front()>maxi&&(!c.empty())){
            maxi=c.front();
            now=3;
        }
        if(now==1){
            a.pop();
        }else{
            if(now==2){
                b.pop();
            }else{
                c.pop();
            }
        }
        if(i%t==0){
            printf("%d ",(1ll*maxi)+(1ll*m)*(1ll*q));
        }
    }
    printf("\n");
    return 0;
}
