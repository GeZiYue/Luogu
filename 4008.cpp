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
#define f(x) fa[x]
#define l(x) ch[x][0]
#define r(x) ch[x][1]
#define s(x) siz[x]
#define v(x) val[x]
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef const int& ci;
void pushup(ci);
bool getid(ci);
void connect(ci, ci, bool);
void rotate(ci);
void splay(int, ci);
int build(ci, ci, ci, const char*);
int find(int);
void insert(ci, ci, const char*);
void del(ci, ci);
void print(ci);
void get(ci, ci);
int fa[N], ch[N][2], siz[N];
char val[N];
int root, id;
char arg[10];
char str[N];
int main () {
    r(1)=s(1)=id=2;
    f(2)=s(2)=root=1;
    int n;
    int now=0;
    read(n);
    for (int i=1; i<=n; ++i) {
        scanf("%s", arg+1);
        if (arg[1]=='M') {
            read(now);
        }else {
            if (arg[1]=='I') {
                int l;
                read(l);
                for (int j=1; j<=l; ++j) {
                    char c;
                    c=getchar();
                    if (c>=32&&c<=126) {
                        str[j]=c;
                    }else {
                        --j;
                    }
                }
                insert(now, l, str);
            }else {
                if (arg[1]=='D') {
                    int l;
                    read(l);
                    del(now, l);
                }else {
                    if (arg[1]=='G') {
                        int l;
                        read(l);
                        get(now, l);
                    }else {
                        if (arg[1]=='P') {
                            --now;
                        }else {
                            ++now;
                        }
                    }
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
void pushup(ci x) {
    s(x)=s(l(x))+1+s(r(x));
}
bool getid(ci x) {
    return r(f(x))==x;
}
void connect(ci x, ci f, bool how) {
    f(x)=f;
    if (f^0) {
        ch[f][how]=x;
    }
}
void rotate(ci x) {
    int y=f(x), R=f(y), ys=getid(x), Rs=getid(y);
    connect(ch[x][ys^1], y, ys);
    connect(y, x, ys^1);
    connect(x, R, Rs);
    pushup(y);
}
void splay(int x, ci to) {
    while (f(x)^to) {
        if (f(f(x))^to) {
            rotate(getid(x)^getid(f(x))?x:f(x));
        }
        rotate(x);
    }
    if (!to) {
        root=x;
    }
}
int build(ci xL, ci xR, ci f, const char *str) {
    if (xL>xR) {
        return 0;
    }
    const int xM=(xL+xR)>>1;
    int now=++id;
    s(now)=xR-xL+1;
    v(now)=str[xM];
    f(now)=f;
    l(now)=build(xL, xM-1, now, str);
    r(now)=build(xM+1, xR, now, str);
    return now;
}
int find(int k) {
    int now=root;
    while (true) {
        int num=s(l(now))+1;
        if (num==k) {
            return now;
        }
        if (num<k) {
            k-=num;
            now=r(now);
        }else {
            now=l(now);
        }
    }
}
void insert(ci x, ci n, const char *str) {
    int l=find(x+1), r=find(x+2);
    splay(l, 0), splay(r, l);
    f(l(r)=build(1, n, 0, str))=r;
}
void del(ci x, ci n) {
    int l=find(x+1), r=find(x+n+2);
    splay(l, 0), splay(r, l);
    l(r)=f(l(r))=0;
}
void print(ci x) {
    if (!x) {
        return;
    }
    print(l(x));
    if (v(x)^0) {
        putchar(v(x));
    }
    print(r(x));
}
void get(ci x, ci n) {
    int l=find(x+1), r=find(x+n+2);
    splay(l, 0), splay(r, l);
    print(l(r)), EL;
}
