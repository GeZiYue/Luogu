#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
#define IsNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define N 300
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef pair<int, int> P;
template<class T1>void read(T1&);
template<class T1>void write(T1);
int gcd(int, int);
int delta[N];
int a[N];
int main() {
	int n;
	read(n);
	int k=0;
	int mini=inf;
	for (int i=1; i<=n; ++i) {
		read(a[i]);
		mini=min(mini, a[i]);
		k=gcd(k, a[i]);
	}
	if (k!=1||mini==1) {
		puts("0");
		return 0;
	}
	for (int i=1; i<mini; ++i) {
		delta[i]=inf;
	}
	priority_queue<P, vector<P>, less<P> >q;
	q.push(P(0, 0));
	while (!q.empty()) {
		P now=q.top();
		q.pop();
		int u=now.second;
		if (delta[u]!=now.first) {
			continue;
		}
		for (int i=1; i<=n; ++i) {
			int v=(u+a[i])%mini;
			if (delta[u]+a[i]<delta[v]) {
				delta[v]=delta[u]+a[i];
				q.push(P(delta[v], v));
			}
		}
	}
	int maxi=0;
	for (int i=1; i<mini; ++i) {
		maxi=max(maxi, delta[i]-mini);
	}
	write(maxi);
	EL;
	return 0;
}
template<class T1>void read(T1& r_e_a_d) {
	char ch=getchar();
	int flag=1;
	T1 num;
	while (!IsNum(ch)) {
		if (ch=='-') {
			flag=-1;
		}
		ch=getchar();
	}
	num=ch-'0';
	ch=getchar();
	while (IsNum(ch)) {
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	r_e_a_d=flag*num;
}
template<class T1>void write(T1 w_r_i_t_e) {
	if (w_r_i_t_e<0) {
		putchar('-');
		write(-w_r_i_t_e);
	}else {
		if (w_r_i_t_e<10) {
			putchar(w_r_i_t_e+'0');
		}else {
			write(w_r_i_t_e/10);
			putchar(w_r_i_t_e%10+'0');
		}
	}
}
int gcd(int a, int b) {
	if (b==0) {
		return a;
	}
	return gcd(b, a%b);
}
