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
#define N 405
#define M 80805
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
inline void add(int, int, int);
bool Dinic_BFS();
int Dinic_DFS(int, int);
int Dinic();
int hed[N], to[M], nxt[M], flow[M];
int dep[N], cur[N];
int S, T;
int V, E;
int main () {
    int t;
    read(t);
    while (t--) {
        int n;
        memset(hed, 0, sizeof(hed));
        E=1;
        read(n);
        S=(n<<1)+1;
        V=T=(n+1)<<1;
        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=n; ++j) {
                int m;
                read(m);
                if (m) {
                    add(i, j+n, 1);
                }
            }
        }
        for (int i=1; i<=n; ++i) {
            add(S, i, 1);
            add(i+n, T, 1);
        }
        puts(Dinic()==n ? "Yes" : "No");
    }
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
void add(int u, int v, int floww) {
    nxt[++E]=hed[u];
    hed[u]=E;
    to[E]=v;
    flow[E]=floww;
    nxt[++E]=hed[v];
    hed[v]=E;
    to[E]=u;
    flow[E]=0;
}
bool Dinic_BFS() {
    for (int i=1; i<=V; ++i) {
        dep[i]=inf;
        cur[i]=hed[i];
    }
    queue<int>q;
    dep[S]=0;
    q.push(S);
    while (!q.empty()) {
        const int u=q.front();
        q.pop();
        for (int i=hed[u]; i; i=nxt[i]) {
            const int v=to[i];
            if (dep[v]==inf&&flow[i]) {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
    return dep[T]^inf;
}
int Dinic_DFS(int u, int minn) {
    if (u==T||minn==0) {
        return minn;
    }
    int ans=0;
    for (int i=cur[u]; i; i=nxt[i]) {
        cur[u]=i;
        const int v=to[i];
        if (dep[v]!=dep[u]+1) {
            continue;
        }
        int now=Dinic_DFS(v, min(minn, flow[i]));
        if (now) {
            flow[i]-=now;
            flow[i^1]+=now;
            minn-=now;
            ans+=now;
            if (minn==0) {
                break;
            }
        }
    }
    return ans;
}
int Dinic() {
    int ans=0;
    while (Dinic_BFS()) {
        ans+=Dinic_DFS(S, inf);
    }
    return ans;
}
