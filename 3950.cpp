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
#define N 300005
#define M 300005
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef const int& ci;
inline void reverse(ci);
inline void pushdown(ci);
inline void rotate(ci);
inline bool nroot(ci);
void splay(int);
void access(int);
int findroot(int);
inline void makeroot(ci);
inline void split(ci, ci);
inline void link(ci, ci);
inline void cut(ci, ci);
int fa[N], ch[N][2];
bool rev[N];
int sta[N];
typedef pair<int, int> P;
P war[M];
int id;
int main () {
    int n, m;
    read(n), read(m);
    for (int i=1; i<n; ++i) {
        int u, v;
        read(u), read(v);
        link(u, v);
    }
    for (int i=1; i<=m; ++i) {
        char ch=getchar();
        while (ch<'C'||ch>'U') {
            ch=getchar();
        }
        if (ch=='U') {
            int x;
            read(x);
            link(war[x].first, war[x].second);
        }else {
            int u, v;
            read(u), read(v);
            if (ch=='Q') {
                puts(findroot(v)==findroot(u)?"Yes":"No");
            }else {
                if (ch=='C') {
                    war[++id]=P(u, v);
                    cut(u, v);
                }
            }
        }
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
void reverse(ci x) {
    rev[x]^=1;
    lc(x)^=rc(x)^=lc(x)^=rc(x);
}
void pushdown(ci x) {
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
void rotate(ci x) {
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
}
bool nroot(ci x) {
    return lc(fa[x])==x||rc(fa[x])==x;
}
void splay(int x) {
    int z, y=sta[z=1]=x;
    while (nroot(y)) {
        sta[++z]=y=fa[y];
    }
    while (z) {
        pushdown(sta[z--]);
    }
    while (nroot(x)) {
        y=fa[x], z=fa[y];
        if (nroot(y)) {
            rotate((lc(y)==x)^(lc(z)==y)?x:y);
        }
        rotate(x);
    }
}
void access(int x) {
    for (int y=0; x; x=fa[y=x]) {
        splay(x), rc(x)=y;
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
void split(ci x, ci y) {
    makeroot(x), access(y), splay(y);
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
    }
}
