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
#define N 2100000
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
inline void ins(int, int, const char*);
inline void del(int, int);
inline void rev(int, int);
inline char get(int);
int fa[N], ch[N][2], siz[N];
bool tag[N];
char v[N];
int root, id;
char arg[10];
char str[N];
int main () {
    rc(1)=siz[1]=id=2;
    fa[2]=siz[2]=root=1;
    int n, now=0;
    read(n);
    for (int i=1; i<=n; ++i) {
        scanf("%s", arg);
        int l;
        switch (arg[0]) {
            case 'M': {
                read(now);
                break;
            }
            case 'I': {
                read(l);
                char c;
                for (int j=1; j<=l; ++j) {
                    c=getchar();
                    if (c<32||c>126) {
                        if (c==10||c==13) {
                            for (int k=j; k<=l; ++k) {
                                str[k]=0;
                            }
                            break;
                        }
                        --j;
                        continue;
                    }
                    str[j]=c;
                }
                ins(now, l, str);
                break;
            }
            case 'D': {
                read(l);
                del(now, l);
                break;
            }
            case 'R': {
                read(l);
                rev(now, l);
                break;
            }
            case 'G': {
                putchar(get(now)), EL;
                break;
            }
            case 'P': {
                --now;
                break;
            }
            case 'N': {
                ++now;
                break;
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
inline void reverse(int x) {
    lc(x)^=rc(x)^=lc(x)^=rc(x);
    tag[x]^=1;
}
inline void pushup(int x) {
    siz[x]=siz[lc(x)]+1+siz[rc(x)];
}
inline void pushdown(int x) {
    if (tag[x]) {
        if (lc(x)) {
            reverse(lc(x));
        }
        if (rc(x)) {
            reverse(rc(x));
        }
        tag[x]=0;
    }
}
inline bool getid(int x) {
    return rc(fa[x])==x;
}
inline void connect(int x, int f, bool how) {
    fa[x]=f;
    ch[f][how]=x;
}
inline void rotate(int x) {
    const int y=fa[x], z=fa[y];
    const bool ys=getid(x), zs=getid(y);
    connect(ch[x][ys^1], y, ys);
    connect(y, x, ys^1);
    connect(x, z, zs);
    pushup(y);
}
void splay(int x, int to) {
    while (fa[x]^to) {
        if (fa[fa[x]]^to) {
            rotate(getid(x)^getid(fa[x])?x:fa[x]);
        }
        rotate(x);
    }
    if (!to) {
        root=x;
    }
}
int find(int k) {
    int now=root, num;
    while (true) {
        pushdown(now);
        num=siz[lc(now)]+1;
        if (num==k) {
            return now;
        }else {
            if (num<k) {
                k-=num;
                now=rc(now);
            }else {
                now=lc(now);
            }
        }
    }
}
int build(int xL, int xR, int f, const char* c) {
    if (xL>xR) {
        return 0;
    }
    const int xM=(xL+xR)>>1, now=++id;
    fa[now]=f;
    v[now]=c[xM];
    siz[now]=xR-xL+1;
    lc(now)=build(xL, xM-1, now, c);
    rc(now)=build(xM+1, xR, now, c);
    return now;
}
void ins(int x, int n, const char* c) {
    const int l=find(x+1), r=find(x+2);
    splay(l, 0), splay(r, l);
    fa[lc(r)=build(1, n, 0, c)]=r;
    pushup(r), pushup(l);
}
void del(int x, int n) {
    const int l=find(x+1), r=find(x+n+2);
    splay(l, 0), splay(r, l);
    lc(r)=fa[lc(r)]=0;
    pushup(r), pushup(l);
}
void rev(int x, int n) {
    const int l=find(x+1), r=find(x+n+2);
    splay(l, 0), splay(r, l);
    reverse(lc(r));
}
char get(int x) {
    const int l=find(x+1), r=find(x+3);
    splay(l, 0), splay(r, l);
    return v[lc(r)];
}
