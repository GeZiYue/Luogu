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
#define N 500005
#define lc(x) (ch[x][0])
#define rc(x) (ch[x][1])
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
void ins(int, int, const int*);
void del(int, int);
void upd(int, int, int);
void rev(int, int);
int sum(int, int);
int mss(int, int);
int fa[N], ch[N][2];
int siz[N], v[N];
int sm[N], ms[N], ls[N], rs[N];
bool is[N];
int ic[N];
int main () {
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
inline void pushup(int x) {
    siz[x]=siz[lc(x)]+1+siz[rc(x)];
    sum[x]=sum[lc(x)]+v[x]+sum[rc(x)];
    ls[x]=max(ls[lc(x)], sm[lc(x)]+v[x]+ls[rc(x)]);
    rs[x]=max(rs[rs(x)], sm[rc(x)]+v[x]+rs[lc(x)]);
}
inline void pushdown(int x) {}
