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
#define N 300005
#define M 300005
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define fa(x) fa[x]
#define tag(x) tag[x]
#define v(x) v[x]
#define sum(x) sum[x]
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef const int& ci;
int v[N], sum[N], fa[N], ch[N][2];
bool tag[N];
int st[N];
void reverse(ci);
void pushup(ci);
void pushdown(ci);
bool nroot(ci);
void rotate(ci);
void splay(int);
void access(int);
int findroot(int);
void makeroot(ci);
void split(ci, ci);
void link(ci, ci);
void cut(ci, ci);
int main () {
    int n, m;
    read(n), read(m);
    for (int i=1; i<=n; ++i) {
        read(v(i));
    }
    for (int i=1; i<=m; ++i) {
        int mod, x, y;
        read(mod), read(x), read(y);
        if (mod==0) {
            split(x, y);
            write(sum(y)), EL;
        }else {
            if (mod==1) {
                link(x, y);
            }else {
                if (mod==2) {
                    cut(x, y);
                }else {
                    splay(x);
                    v(x)=y;
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
    lc(x)^=rc(x)^=lc(x)^=rc(x);
    tag(x)^=1;
}
void pushup(ci x) {
    sum(x)=sum(lc(x))^sum(rc(x))^v(x);
}
void pushdown(ci x){
    if (tag(x)) {
        if (lc(x)) {
            reverse(lc(x));
        }
        if (rc(x)) {
            reverse(rc(x));
        }
        tag(x)=false;
    }
}
bool nroot(ci x) {
    return lc(fa(x))==x||rc(fa(x))==x;
}
void rotate(ci x) {
    const int y=fa(x), R=fa(y), ys=rc(y)==x, Rs=rc(R)==y, w=ch[x][ys^1];
    if (nroot(y)) {
        ch[R][Rs]=x;
    }
    ch[x][ys^1]=y;
    ch[y][ys]=w;
    if (w) {
        fa(w)=y;
    }
    fa(x)=R;
    fa(y)=x;
    pushup(y);
}
void splay(int x) {
    int y=x, z;
    st[z=1]=y;
    while (nroot(y)) {
        st[++z]=y=fa(y);
    }
    while (z) {
        pushdown(st[z--]);
    }
    while (nroot(x)) {
        y=fa(x), z=fa(y);
        if (nroot(y)) {
            rotate((lc(y)==x)^(lc(z)==y)?x:y);
        }
        rotate(x);
    }
    pushup(x);
}
void access(int x) {
    for (int y=0; x; x=fa(y=x)) {
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
void split(ci x, ci y) {
    makeroot(x), access(y), splay(y);
}
void link(ci x, ci y) {
    makeroot(x);
    if (findroot(y)^x) {
        fa(x)=y;
    }
}
void cut(ci x, ci y) {
    makeroot(x);
    if (findroot(y)==x&&fa(y)==x&&!lc(y)) {
        fa(y)=rc(x)=0;
        pushup(x);
    }
}
