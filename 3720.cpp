#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define N 100005
#define M 500005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef pair<int, int> P;
template<class T1>void read(T1&);
template<class T1>void write(T1);
class zkw {
private:
	#define ls(x) (x<<1)
	#define rs(x) (x<<1|1)
	P mini[N<<2];
	int Begin;
public:
	void Build(int, int*);
	void Update(int, int);
	P Query();
}q;
class Graph {
private:
	int PointNum, EdgeNum;
	int hed[N], nxt[M], to[M], dis[M];
	int delta[N];
public:
	void Change(int);
	void Add(int, int, int);
	void Dijkstra(int);
	int Query(int);
}GPS1, GPS2, ans;
int x[M], y[M], w1[M], w2[M];
int main() {
	int n, m;
	read(n);
	read(m);
	GPS1.Change(n);
	GPS2.Change(n);
	for (int i=1; i<=m; ++i) {
		read(x[i]);
		read(y[i]);
		read(w1[i]);
		read(w2[i]);
		GPS1.Add(y[i], x[i], w1[i]);
		GPS2.Add(y[i], x[i], w2[i]);
	}
	GPS1.Dijkstra(n);
	GPS2.Dijkstra(n);
	ans.Change(n);
	for (int i=1; i<=m; ++i) {
		int now=2;
		if (GPS1.Query(y[i])!=inf&&GPS1.Query(y[i])+w1[i]==GPS1.Query(x[i])) {
			--now;
		}
		if (GPS2.Query(y[i])!=inf&&GPS2.Query(y[i])+w2[i]==GPS2.Query(x[i])) {
			--now;
		}
		ans.Add(x[i], y[i], now);
	}
	ans.Dijkstra(1);
	write(ans.Query(n));
	EL;
	return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
	T1 num;
	char ch;
	int flag=1;
	ch=getchar();
	while (!isNum(ch)) {
		if (ch=='-') {
			flag=-1;
		}
		ch=getchar();
	}
	num=ch-'0';
	ch=getchar();
	while (isNum(ch)) {
		num=(num<<1)+(num<<3)+ch-'0';
		ch=getchar();
	}
	r_e_a_d=num*flag;
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
void zkw::Build(int n, int* num) {
	Begin=n;
	while (Begin^((-Begin)&Begin)) {
		Begin-=((-Begin)&Begin);
	}
	Begin<<=1;
	for (int i=1; i<=n; ++i) {
		mini[Begin+i]=P(num[i], i);
	}
	for (int i=n+1; i<=Begin+1; ++i) {
		mini[Begin+i]=P(inf, 0);
	}
	for (int i=Begin-1; i>=1; --i) {
		mini[i]=min(mini[ls(i)], mini[rs(i)]);
	}
}
void zkw::Update(int x, int num) {
	mini[Begin+x].first=num;
	for (int i=Begin+x; i^1; i>>=1) {
		mini[i>>1]=min(mini[i], mini[i^1]);
	}
}
P zkw::Query() {
	return mini[1];
}
void Graph::Change(int n) {
	PointNum=n;
}
void Graph::Add(int x, int y, int diss) {
	nxt[++EdgeNum]=hed[x];
	hed[x]=EdgeNum;
	to[EdgeNum]=y;
	dis[EdgeNum]=diss;
}
void Graph::Dijkstra(int Source) {
	for (int i=1; i<=PointNum; ++i) {
		delta[i]=inf;
	}
	delta[Source]=0;
	q.Build(PointNum, delta);
	while (1) {
		P now=q.Query();
		if (now.first==inf) {
			break;
		}
		int u=now.second;
		q.Update(u, inf);
		for (int i=hed[u]; i; i=nxt[i]) {
			int v=to[i];
			if (delta[u]+dis[i]<delta[v]) {
				delta[v]=delta[u]+dis[i];
				q.Update(v, delta[v]);
			}
		}
	}
}
int Graph::Query(int x) {
	return delta[x];
}
