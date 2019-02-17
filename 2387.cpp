#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define inf 2147483647
#define N 50005
#define M 100005
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef const int& ci;
inline void access(int);
inline int findroot(int);
inline void makeroot(ci);
inline int query(ci, ci);
inline void link(ci, ci);
inline void cut(ci, ci);
inline int find(ci);
inline bool connected(ci, ci);
inline void merge(ci, ci);
int val[N+M], maxn[N+M];
int fa[N+M], ch[N+M][2];
bool rev[N+M];
int st[N+M];
int f[N];
class Edge {
public:
    int u, v, a, b;
    bool operator<(const Edge& i) const {
        if (a==i.a) {
            return b<i.b;
        }
        return a<i.a;
    }
}e[M];
int main () {
    int n, m;
    read(n), read(m);
    for (register int i=1; i<=n; ++i) {
        f[i]=i;
    }
    for (register int i=1; i<=m; ++i) {
        read(e[i].u), read(e[i].v), read(e[i].a), read(e[i].b);
    }
    sort(e+1, e+m+1);
    for (int i=1; i<=m; ++i) {
        val[n+i]=e[i].b;
    }
    int ans=inf;
    for (register int i=1, u, v, now; i<=m; ++i) {
        u=e[i].u, v=e[i].v;
        if (!connected(u, v)) {
            merge(u, v);
        }else {
            now=query(u, v);
            if (val[now]>e[i].b) {
                cut(e[now-n].u, now), cut(now, e[now-n].v);
            }else {
                continue;
            }
        }
        link(e[i].u, i+n), link(i+n, e[i].v);
        if (connected(1, n)) {
            ans=min(ans, e[i].a+val[query(1, n)]);
        }
        if (e[i].a>ans) {
            break;
        }
    }
    write(ans==inf?-1:ans), EL;
    return 0;
}
template<class T>void read(T &Re) {
    register T k=0;
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
inline void reverse(ci x) {
    rev[x]^=1;
    lc(x)^=rc(x)^=lc(x)^=rc(x);
}
inline void pushup(ci x) {
    maxn[x]=x;
    if (lc(x)&&val[maxn[lc(x)]]>val[maxn[x]]) {
        maxn[x]=maxn[lc(x)];
    }
    if (rc(x)&&val[maxn[rc(x)]]>val[maxn[x]]) {
        maxn[x]=maxn[rc(x)];
    }
}
inline void pushdown(ci x) {
    if (rev[x]) {
        if (lc(x)) {
            reverse(lc(x));
        }
        if (rc(x)) {
            reverse(rc(x));
        }
        rev[x]=false;
    }
}
inline bool nroot(ci x) {
    return lc(fa[x])==x||rc(fa[x])==x;
}
inline void rotate(ci x) {
    const int y=fa[x], r=fa[y], ys=rc(y)==x, rs=rc(r)==y, w=ch[x][ys^1];
    if (nroot(y)) {
        ch[r][rs]=x;
    }
    ch[x][ys^1]=y;
    ch[y][ys]=w;
    if (w) {
        fa[w]=y;
    }
    fa[x]=r;
    fa[y]=x;
    pushup(y);
}
inline void pushall(int x) {
    if (nroot(x)) {
        pushall(fa[x]);
    }
    pushdown(x);
}
inline void splay(int x) {
    pushall(x);
    int y, z;
    while (nroot(x)) {
        y=fa[x], z=fa[y];
        if (nroot(y)) {
            rotate((lc(z)==y)^(lc(y)==x)?x:y);
        }
        rotate(x);
    }
    pushup(x);
}
void access(int x) {
    for (register int y=0; x; x=fa[y=x]) {
        splay(x), rc(x)=y, pushup(x);
    }
}
int findroot(int x) {
    access(x), splay(x);
    while (lc(x)) {
        x=lc(x);
    }
    splay(x);
    return x;
}
void makeroot(ci x) {
    access(x), splay(x), reverse(x);
}
int query(ci x, ci y) {
    makeroot(x), access(y), splay(y);
    return maxn[y];
}
void link(ci x, ci y) {
    makeroot(x);
    if (findroot(y)^x) {
        fa[x]=y;
    }
}
void cut(ci x, ci y) {
    makeroot(x);
    if (findroot(y)==x&&fa[y]==x&&!lc(y)) {
        fa[y]=rc(x)=0;
        pushup(x);
    }
}
int find(ci x) {
    return f[x]==x?x:f[x]=find(f[x]);
}
bool connected(ci x, ci y) {
    const int fx=find(x), fy=find(y);
    return fx==fy;
}
void merge(ci x, ci y) {
    const int fx=find(x), fy=find(y);
    if (fx^fy) {
        f[fy]=fx;
    }
}
