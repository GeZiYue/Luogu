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
#define N 75
#define M 1005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
class Network {
private:
    int hed[N], nxt[M<<1], to[M<<1], flow[M<<1], id=1;
    int cur[N], dep[N];
    int n;
    int s, t;
    bool BFS();
    int DFS(const int&, int);
public:
    void Clear(const int& nn, const int& ss, const int& tt){n=nn;s=ss;t=tt;}
    void Add(const int&, const int&, const int&);
    int Dinic();
}G;
int main () {
    int m;
    read(m);
    G.Clear(60, 1, 26);
    for (int i=1; i<=m; ++i) {
        char c1, c2;
        int floww;
        cin>>c1>>c2;
        read(floww);
        int u=c1-'A'+1, v=c2-'A'+1;
        if (c1>='a') {
            u-='a'-'A'-26;
        }
        if (c2>='a') {
            v-='a'-'A'-26;
        }
        G.Add(u, v, floww);
        G.Add(v, u, 0);
    }
    write(G.Dinic());
    EL;
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
template<class Fir, class... Res>void read(Fir& Fi, Res&... Re) {
    read(Fi);
    read(Re...);
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
template<class Fir, class... Res>void write(const Fir& Fi, const Res&... Re) {
    write(Fi);
    putchar(' ');
    write(Re...);
}
void Network::Add(const int& u, const int& v, const int& flw) {
    nxt[++id]=hed[u];
    hed[u]=id;
    to[id]=v;
    flow[id]=flw;
}
bool Network::BFS() {
    for (int i=1; i<=n; ++i) {
        dep[i]=inf;
        cur[i]=hed[i];
    }
    dep[s]=0;
    queue<int>q;
    q.push(s);
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
    return dep[t]!=inf;
}
int Network::DFS(const int& u, int minn) {
    if (minn==0||u==t) {
        return minn;
    }
    int res=0;
    for (int i=cur[u]; i; i=nxt[i]) {
        cur[u]=i;
        const int v=to[i];
        if (dep[v]!=dep[u]+1) {
            continue;
        }
        int now=DFS(v, min(minn, flow[i]));
        if (now) {
            res+=now;
            minn-=now;
            flow[i]-=now;
            flow[i^1]+=now;
            if (minn==0) {
                break;
            }
        }
    }
    return res;
}
int Network::Dinic() {
    int res=0;
    while (BFS()) {
        res+=DFS(s, inf);
    }
    return res;
}
