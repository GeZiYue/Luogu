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
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
const int N=105, M=10005;
int hed[N], nxt[M], to[M], dis[M], id=1;
int n, m;
int delta[N];
void add(int, int, int);
void twice(int);
void div(int);
void dijkstra(int);
int las[N];
int bef[N];
int main () {
    read(n), read(m);
    for (int i=1; i<=m; ++i) {
        int u, v, dis;
        read(u), read(v), read(dis);
        add(u, v, dis);
        add(v, u, dis);
    }
    dijkstra(1);
    for (int i=1; i<=n; ++i) {
        las[i]=bef[i];
    }
    int fi=delta[n];
    int now=n;
    int ans=0;
    while (las[now]) {
        twice(las[now]), twice(las[now]^1);
        dijkstra(1);
        ans=max(ans, delta[n]-fi);
        div(las[now]), div(las[now]^1);
        now=to[las[now]^1];
    }
    write(ans), EL;
    return 0;
}
template<class T>void read(T &Re) {
    T k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch)) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    Re=flag*k;
}
template<class T>void write(const T& Wr) {
    if (Wr<0) {
        putchar('-');
        write(-Wr);
    }else {
        if (Wr<10) {
            putchar(Wr+'0');
        }else {
            write(Wr/10);
            putchar((Wr%10)+'0');
        }
    }
}
void add(int u, int v, int diss) {
    nxt[++id]=hed[u];
    hed[u]=id;
    to[id]=v;
    dis[id]=diss;
}
void twice(int en) {
    dis[en]<<=1;
}
void div(int en) {
    dis[en]>>=1;
}
void dijkstra(int S) {
    for (int i=1; i<=n; ++i) {
        delta[i]=inf;
    }
    delta[S]=0;
#define P pair<int, int>
#define fi first
#define se second
    priority_queue<P> q;
    q.push(P(0, S));
    while (!q.empty()) {
        const P now=q.top();
        q.pop();
        if (delta[now.se]<now.fi) {
            continue;
        }
        const int u=now.se;
        for (int i=hed[u]; i; i=nxt[i]) {
            const int v=to[i];
            if (delta[u]+dis[i]<delta[v]) {
                q.push(P(delta[v]=delta[u]+dis[i], v));
                bef[v]=i;
            }
        }
    }
#undef P
#undef fi
#undef se
}
