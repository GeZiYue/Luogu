#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define mk make_pair
using namespace std;
typedef long long int ll;
ll dp[500005];
int q[500005];
int head,tail;
ll a[500005],b[500005];
int main(){
    ll n,m,k,L,M,R,i,j,x,y,l;
    ll maxi,now;
    cin>>n>>m>>k;
    for(i=1;i<=n;i++){
        cin>>a[i]>>b[i];
    }
    L=-1;
    R=a[n];
    while(L<R){
        M=(L+R)>>1;
        x=max(1ll,m-M);
        y=m+M;
        maxi=-2147483647;
        q[1]=0;
        l=0;
        head=1;
        tail=0;
		for(i=1;i<=n;i++){
			dp[i]=-2147483647;
		}
        for(i=1;i<=n;i++){
        	while(a[i]-a[l]>=x&&l<i){
        		while(dp[q[tail]]<=dp[l]&&head<=tail){
					tail--;
				}
				q[++tail]=l;
				l++;
			}
			while(a[i]-a[q[head]]>y&&head<=tail){
				head++;
			}
			if(head>tail||dp[q[head]]==-2147483647){
				continue;
			}else{
				dp[i]=dp[q[head]]+b[i];
			}
			maxi=max(maxi,dp[i]);
        }
        if(maxi>=k){
            R=M;
        }else{
            L=M+1;
        }
    }
    cout<<L<<endl;
    return 0;
}
