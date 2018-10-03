#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
int a[40005],ans;
void gwork(int s[],int L,int R);
int main(){
    int n,i;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>a[i];
    }
    gwork(a,1,n);
    cout<<ans<<endl;
}
void gwork(int s[],int L,int R){
    if(L==R){
        return;
    }
    int i,j,k,M=(L+R)>>1;
    int l[40005];
    for(i=L;i<=R;i++){
        l[i]=s[i];
    }
    gwork(l,L,M);
    gwork(l,M+1,R);
    i=L-1;
	for(j=L,k=M+1;j<=M&&k<=R;){
		if(l[j]<=l[k]){
			s[++i]=l[j++];
		}else{
			s[++i]=l[k++];
            ans+=M-j+1;
		}
	}
	while(j<=M){
		s[++i]=l[j++];
	}
	while(k<=R){
		s[++i]=l[k++];
	}
    return;
}
