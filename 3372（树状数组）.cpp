#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define gbit(a) (a&(-a))
#define Int(a) read(a)
#define ll unsigned long long
void read(ll &r_e_a_d);
void add(ll a[],ll i,ll sum);
ll sum(ll a[],ll i);
ll n,m,ans1[100005],ans2[100005];
int main(){
	ll a,b=0,c,d,i;
	Int(n);Int(m);
	for(i=1;i<=n;i++){
		Int(a);
		add(ans1,i,a-b);
        add(ans2,i,(a-b)*(i-1));
		b=a;
	}
	for(i=1;i<=m;i++){
		Int(a);
		if(a==1){
			Int(b);Int(c);Int(d);
			add(ans1,b,d);
			add(ans1,c+1,-d);
            add(ans2,b,d*(b-1));
            add(ans2,c+1,-d*c);
		}else{
			Int(b);Int(c);
			cout<<c*sum(ans1,c)-(b-1)*sum(ans1,b-1)-sum(ans2,c)+sum(ans2,b-1)<<endl;
		}
	}
	return 0;
}
void add(ll a[],ll i,ll sum){
    while(i<=n){
        a[i]+=sum;
        i+=gbit(i);
    }
    return;
}
ll sum(ll a[],ll i){
    ll num=0;
    while(i){
        num+=a[i];
        i-=gbit(i);
    }
    return num;
}
void read(ll &r_e_a_d){
    ll k=0;
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
