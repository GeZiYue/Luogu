#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
void read(int &r_e_a_d);
char a[2005],b[2005];
int dp[2005][2005];
int main(){
    int n,m,k,i,j;
    cin>>a+1>>b+1>>k;
    n=strlen(a+1);
    m=strlen(b+1);
    for(i=1;i<=n;i++){
        dp[i][0]=dp[i-1][0]+k;
    }
    for(i=1;i<=m;i++){
        dp[0][i]=dp[0][i-1]+k;
    }
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            dp[i][j]=min(min(dp[i-1][j]+k,dp[i][j-1]+k),dp[i-1][j-1]+abs(int(a[i])-int(b[j])));
        }
    }
    cout<<dp[n][m]<<endl;
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
