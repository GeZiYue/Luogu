#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
using namespace std;
char a[2000];
char gwork(int n,int l);
int main(){
	int n,i;
	char c;
	cin>>n;
	n=(1<<n);
	for(i=1;i<=n;i++){
		cin>>c;
        if(c=='0'){
            a[i]='B';
        }else{
            a[i]='I';
        }
	}
	gwork(n,1);
    cout<<endl;
	return 0;
}
char gwork(int n,int l){
	char L,R;
	if(n==1){
		L=R=a[l];
        goto con;
	}
	L=gwork(n/2,l);
	R=gwork(n/2,l+n/2);
    con:;
	if(L==R){
        cout<<L;
        return L;
    }else{
        cout<<'F';
        return 'F';
    }
}
