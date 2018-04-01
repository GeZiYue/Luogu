#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
int a[500005],b[500005];
unsigned long long ans;
void gwork(int L,int R);
void read(int &r_e_a_d);
int main(){
    int n,i;
    Int(n);
    for(i=1;i<=n;i++){
        Int(a[i]);
    }
    gwork(1,n);
    cout<<ans<<endl;
}
void gwork(int L,int R){
    if(L==R){
        return;
    }
    int i,j,k,M=(L+R)>>1;
    gwork(L,M);
    gwork(M+1,R);
    i=L-1;
	for(j=L,k=M+1;j<=M&&k<=R;){
		if(a[j]<=a[k]){
			b[++i]=a[j++];
		}else{
			b[++i]=a[k++];
            ans+=M-j+1;
		}
	}
	while(j<=M){
		b[++i]=a[j++];
	}
	while(k<=R){
		b[++i]=a[k++];
	}
    for(i=L;i<=R;i++){
        a[i]=b[i];
    }
    return;
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
