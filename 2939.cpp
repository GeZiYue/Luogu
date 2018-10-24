#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 1000005
#define M 10000005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class P {
public:
    int first, second;
    bool operator<(P i) const {
        return first>i.first;
    }
    P(int x, int y):first(x), second(y){}
};
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
}G;
int main () {
    int n, m, k;
    read(n);
    read(m);
    read(k);
    G.Change(n*(k+1));
    for (int i=1; i<=m; ++i) {
        int x, y, w;
        read(x);
        read(y);
        read(w);
        for (int j=0; j<=k; ++j) {
            G.Add((x-1)*(k+1)+j, (y-1)*(k+1)+j, w);
            G.Add((y-1)*(k+1)+j, (x-1)*(k+1)+j, w);
            if (j!=k) {
                G.Add((x-1)*(k+1)+j, (y-1)*(k+1)+j+1, 0);
                G.Add((y-1)*(k+1)+j, (x-1)*(k+1)+j+1, 0);
            }
        }
    }
    for (int i=1; i<=n; ++i) {
        for (int j=0; j<k; ++j) {
            G.Add((i-1)*(k+1)+j, (i-1)*(k+1)+j+1, 0);
        }
    }
    G.Dijkstra(0);
    write(G.Query((n-1)*(k+1)+k));
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d = flag*k;
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
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
void Graph::Change(int n) {
	PointNum=n;
}
void Graph::Add(int x, int y, int diss) {
	nxt[++EdgeNum]=hed[x], hed[x]=EdgeNum, to[EdgeNum]=y, dis[EdgeNum]=diss;
}
void Graph::Dijkstra(int Source) {
    priority_queue<P>q;
	for (int i=1; i<=PointNum; ++i) {
		delta[i]=inf;
	}
	delta[Source]=0;
    q.push(P(0, Source));
	while (!q.empty()) {
		P now=q.top();
        q.pop();
        int u=now.second;
		if (now.first!=delta[u]) {
			continue;
		}
		for (int i=hed[u]; i; i=nxt[i]) {
			int v=to[i];
			if (delta[u]+dis[i]<delta[v]) {
				delta[v]=delta[u]+dis[i];
				q.push(P(delta[v], v));
			}
		}
	}
}
int Graph::Query(int x) {
	return delta[x];
}
