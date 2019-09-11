#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<string>
#include<stack>
#include<queue>
#include<map>
#include<set>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 100005
#define M 325
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
typedef long long int ll;
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
ll v[N];
int bel[N], l[M], r[M];
ll tag[M], sum[M];
void GetBlock(int);
void Update(int, int, ll);
ll Query(int, int);
int main() {
	int n;
    int m;
	read(n);
    read(m);
	for (int i=1; i<=n; ++i) {
		read(v[i]);
	}
	GetBlock(n);
	for (int i=1; i<=m; ++i) {
		int mod, l, r;
        read(mod);
        read(l);
        read(r);
        if (mod==1) {
            int x;
            read(x);
            Update(l, r, x);
        }else {
            write(Query(l, r));
            EL;
        }
	}
    return 0;
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        if(ch=='-'){
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch)){
        k=((k<<1)+(k<<3)+ch-'0');
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
void GetBlock(int n) {
	int blocklen=int(sqrt(n));
	int m=n/blocklen+(n%blocklen!=0);
	for (int i=1; i<=n; ++i) {
		bel[i]=(i-1)/blocklen+1;
		sum[bel[i]]+=v[i];
	}
	for (int i=1; i<=m; ++i) {
		l[i]=(i-1)*blocklen+1;
		r[i]=i*blocklen;
	}
	r[m]=n;
}
void Update(int L, int R, ll x) {
	for (int i=L; i<=min(r[bel[L]], R); ++i) {
		v[i]+=x;
		sum[bel[i]]+=x;
	}
	if (bel[L]^bel[R]) {
		for (int i=l[bel[R]]; i<=R; ++i) {
			v[i]+=x;
			sum[bel[i]]+=x;
		}
	}
	for (int i=bel[L]+1; i<bel[R]; ++i) {
		tag[i]+=x;
	}
}
ll Query(int L, int R) {
	ll ans=0;
	for (int i=L; i<=min(r[bel[L]], R); ++i) {
		ans+=v[i]+tag[bel[i]];
	}
	if (bel[L]^bel[R]) {
		for (int i=l[bel[R]]; i<=R; ++i) {
			ans+=v[i]+tag[bel[i]];
		}
	}
	for (int i=bel[L]+1; i<bel[R]; ++i) {
		ans+=sum[i]+tag[i]*(r[i]-l[i]+1);
	}
	return ans;
}
