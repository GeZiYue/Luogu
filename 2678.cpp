#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
long long a[50005];
int main(){
    long long n,m,k,L,R,M,now,sum,i;
    cin>>k>>n>>m;
    if(n==0){
        cout<<k<<endl;
        return 0;
    }
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    a[++n]=k;
    L=1;
    R=k;
    while(L<R){
        M=(L+R)>>1;
        now=0;
        sum=0;
        for(i=1;i<=n;i++){
            if(a[i]-now>=M){
                now=a[i];
            }else{
                sum++;
                if(sum>m){
                    break;
                }
            }
        }
        if(sum<=m){
            L=M+1;
        }else{
            R=M;
        }
    }
    cout<<L-1<<endl;
}
