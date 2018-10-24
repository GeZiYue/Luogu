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
#define N 300005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef pair<int, int> P;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Graph {
private:
	int PointNum, EdgeNum;
	int hed[N];
    int dis[N];
	int delta[N];
public:
	void Change(int);
    void Add(int);
	void Dijkstra(int);
	int Query(int);
}G;
int gcd(int, int);
int l[N], id;
int main () {
    int n, m;
    read(n);
    read(m);
    int r=0, mini=inf;
    for (int i=1; i<=n; ++i) {
        int x;
        read(x);
        for (int j=x; j>=max(1, x-m); --j) {
            l[++id]=j;
            r=gcd(r, l[id]);
            mini=min(mini, l[id]);
            G.Add(l[id]);
        }
    }
    if (r!=1||mini==1) {
        write(-1);
        EL;
        return 0;
    }
    G.Change(mini);
    G.Dijkstra(0);
    int ans=0;
    for (int i=1; i<mini; ++i) {
        ans=max(ans, G.Query(i)-mini);
    }
    write(ans);
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
int gcd(int a, int b) {
    if (b==0) {
        return a;
    }
    return gcd(b, a%b);
}
void Graph::Change(int n) {
	PointNum=n;
}
void Graph::Add(int x) {
    dis[++EdgeNum]=x;
}
void Graph::Dijkstra(int Source) {
    priority_queue<P, vector<P>, greater<P> >q;
	for (int i=0; i<PointNum; ++i) {
		delta[i]=inf;
	}
	delta[Source]=0;
	q.push(P(0, Source));
	while (!q.empty()) {
		P now=q.top();
		int u=now.second;
        q.pop();
        if (now.first!=delta[u]) {
            continue;
        }
		for (int i=1; i<=EdgeNum; ++i) {
			int v=(u+dis[i])%PointNum;
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
