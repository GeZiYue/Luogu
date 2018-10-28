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
#define N 10005
#define M 400005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef pair<int, int> P;
template<class T1>void read(T1&);
template<class T1>void write(T1);
class Graph {
public:
	int PointNum, EdgeNum;
	int hed[N], nxt[M], to[M], wei[M];
	int delta[N];
	void Add(int, int, int);
	void Dijkstra(int);
}bef, aft;
int x[M], y[M];
bool flag[N];
int main() {
	int n, m;
	read(n);
	read(m);
	aft.PointNum=bef.PointNum=n;
	for (int i=1; i<=m; ++i) {
		read(x[i]);
		read(y[i]);
		aft.Add(y[i], x[i], 1);
	}
	int s, t;
	read(s);
	read(t);
	aft.Dijkstra(t);
	for (int i=1; i<=n; ++i) {
		flag[i]=true;
	}
	for (int u=1; u<=n; ++u) {
		if (aft.delta[u]==inf) {
			for (int i=aft.hed[u]; i; i=aft.nxt[i]) {
				int v=aft.to[i];
				flag[v]=false;
			}
		}
	}
	if (!flag[s]) {
		write(-1);
		EL;
		return 0;
	}
	for (int i=1; i<=m; ++i) {
		if (flag[x[i]]&&flag[y[i]]) {
			bef.Add(x[i], y[i], 1);
		}
	}
	bef.Dijkstra(s);
	if (bef.delta[t]==inf) {
		write(-1);
	}else {
		write(bef.delta[t]);
	}
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
void Graph::Add(int x, int y, int dis) {
	nxt[++EdgeNum]=hed[x];
	hed[x]=EdgeNum;
	to[EdgeNum]=y;
	wei[EdgeNum]=dis;
}
void Graph::Dijkstra(int Source) {
	for (int i=1; i<=PointNum; ++i) {
		delta[i]=inf;
	}
	delta[Source]=0;
	priority_queue<P, vector<P>, greater<P> >q;
	q.push(P(0, Source));
	while (!q.empty()) {
		P now=q.top();
		q.pop();
		if (delta[now.second]!=now.first) {
			continue;
		}
		int u=now.second;
		for (int i=hed[u]; i; i=nxt[i]) {
			int v=to[i];
			if (delta[u]+wei[i]<delta[v]) {
				delta[v]=delta[u]+wei[i];
				q.push(P(delta[v], v));
			}
		}
	}
}
