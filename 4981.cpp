#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
ll pow(ll, ll, ll);
int main() {
	int t;
	read(t);
	while(t--) {
        ll n;
        read(n);
        write(pow(n, n-1, 1000000009));
        EL;
	}
	return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
	T1 k = 0;
	char ch = getchar();
	int flag = 1;
	while (!isNum(ch)) {
		if (ch == '-') {
			flag = -1;
		}
		ch = getchar();
	}
	while (isNum(ch)) {
		k = (k << 1) + (k << 3) + ch - '0';
		ch = getchar();
	}
	r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
	if (w_r_i_t_e < 0) {
		putchar('-');
		write(-w_r_i_t_e);
	}
	else {
		if (w_r_i_t_e < 10) {
			putchar(w_r_i_t_e + '0');
		}
		else {
			write(w_r_i_t_e / 10);
			putchar((w_r_i_t_e % 10) + '0');
		}
	}
}
ll pow(ll a, ll b, ll mod) {
	ll ans=1, now=a;
	while (b) {
		if (b&1) {
			ans=ans*now%mod;
		}
		now=now*now%mod;
        b>>=1;
	}
	return ans;
}
