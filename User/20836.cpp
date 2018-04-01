#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define ll unsigned long long int
#define N 100005
#define M 1000005
#define inf 9223372036854775807
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
ll Get(int x);
char Be[M];
ll Bnum[N],Tnum[N];
int sum[M];
ll len;
int main(){
	ll m,i,a,b;
	int id;
	scanf("%s",Be);
	len=strlen(Be);
	Tnum[1]=Tnum[2]=Bnum[2]=len;
	for(i=0;i<len;i++){
		Bnum[1]+=(Be[i]=='B');
		Tnum[2]+=(Be[i]=='B');
		sum[i+1]=sum[i]+(Be[i]=='B');
	}
	for(id=2;Tnum[id]<=inf;id++){
		Tnum[id+1]=Tnum[id]+Tnum[id-1];
		Bnum[id+1]=Bnum[id]+Bnum[id-1];
	}
	for(i=1;i<=10;i++){
		cout<<Tnum[i]<<' '<<Bnum[i]<<endl;
	}
	read(m);
	for(i=1;i<=m;i++){
		read(a);
		read(b);
		if(a==0){
			a=1;
		}
		printf("%lld\n",Get(b)-Get(a-1));
	}
	return 0;
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        ch=getchar();
        if(ch=='-'){
            flag=-1;
        }
    }
    while(isNum(ch)){
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
template<class T1>void write(T1 w_r_i_t_e){
    if(w_r_i_t_e<0){
        putchar('-');
        write(-w_r_i_t_e);
    }else{
        if(w_r_i_t_e<10){
            putchar(w_r_i_t_e+'0');
        }else{
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
ll Get(int x){
	ll ans=0;
	ll l=x;
	int i=1;
	if(l<=len){
		ans+=sum[l];
		return ans;
	}
	while(Tnum[i]<=l){
		i++;
	}
	for(;i>=1&&l>0;i--){
		if(Tnum[i]<=l){
			l-=Tnum[i];
			ans+=Bnum[i];
		}
	}
	return ans;
}
