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
#define N 1000005
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
typedef const int& ci;
void PushUp(ci);
void PushDown(ci);
void Build(ci, ci, ci);
void Update(ci, ci, ci, ci, ci, ci);
int minn[N<<2], tag[N<<2];
int r[N];
int main () {
    int n, m;
    read(n, m);
    for (int i=1; i<=n; ++i) {
        read(r[i]);
    }
    Build(1, 1, n);
    for (int i=1; i<=m; ++i) {
        int d, s, t;
        read(d, s, t);
        Update(1, 1, n, s, t, -d);
        if (minn[1]<0) {
            write(-1);EL;write(i);EL;return 0;
        }
    }
    write(0);
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
void PushUp(ci x) {
    minn[x]=min(minn[ls(x)], minn[rs(x)]);
}
void PushDown(ci x) {
    if (tag[x]) {
        minn[ls(x)]+=tag[x];
        minn[rs(x)]+=tag[x];
        tag[ls(x)]+=tag[x];
        tag[rs(x)]+=tag[x];
        tag[x]=0;
    }
}
void Build(ci x, ci xL, ci xR) {
    if (xL==xR) {
        minn[x]=r[xL];
        return;
    }
    int xM=(xL+xR)>>1;
    Build(ls(x), xL, xM);
    Build(rs(x), xM+1, xR);
    PushUp(x);
}
void Update(ci x, ci xL, ci xR, ci uL, ci uR, ci num) {
    if (xL>=uL&&xR<=uR) {
        minn[x]+=num;
        tag[x]+=num;
        return;
    }
    if (xL>uR||xR<uL) {
        return;
    }
    PushDown(x);
    int xM=(xL+xR)>>1;
    Update(ls(x), xL, xM, uL, uR, num);
    Update(rs(x), xM+1, xR, uL, uR, num);
    PushUp(x);
}
