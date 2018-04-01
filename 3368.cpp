#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define gbit(a) (a&(-a))
#define Int(a) read(a)
void read(int &r_e_a_d);
void add(int i,int sum);
int sum(int i);
int n,m,ans[500005];
int main(){
	int a,b=0,c,d,i;
	Int(n);Int(m);
	for(i=1;i<=n;i++){
		Int(a);
		add(i,a-b);
		b=a;
	}
	for(i=1;i<=m;i++){
		Int(a);
		if(a==1){
			Int(b);Int(c);Int(d);
			add(b,d);
			add(c+1,-d);
		}else{
			Int(b);
			printf("%d\n",sum(b));
		}
	}
	return 0;
}
void add(int i,int sum){
    while(i<=n){
        ans[i]+=sum;
        i+=gbit(i);
    }
    return;
}
int sum(int i){
    int num=0;
    while(i){
        num+=ans[i];
        i-=gbit(i);
    }
    return num;
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