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
#define N 200005
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
void PushUp(int);
void Build(int, int, int);
int Query(int, int, int, int, int);
void Update(int, int, int, int, int);
int maxn[N<<2];
int a[N];
int main () {
    int n, m;
    read(n, m);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
    }
    Build(1, 1, n);
    for (int i=1; i<=m; ++i) {
        char ch;
        int l, r;
        cin>>ch;
        read(l, r);
        if (ch=='Q') {
            write(Query(1, 1, n, l, r));
            EL;
        }else {
            Update(1, 1, n, l, r);
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
void PushUp(int x) {
    maxn[x]=max(maxn[ls(x)], maxn[rs(x)]);
}
void Build(int x, int xL, int xR) {
    if (xL==xR) {
        maxn[x]=a[xL];
        return;
    }
    int xM=(xL+xR)>>1;
    Build(ls(x), xL, xM);
    Build(rs(x), xM+1, xR);
    PushUp(x);
}
int Query(int x, int xL, int xR, int qL, int qR) {
    if (xL>=qL&&xR<=qR) {
        return maxn[x];
    }
    if (xL>qR||xR<qL) {
        return 0;
    }
    int xM=(xL+xR)>>1;
    return max(Query(ls(x), xL, xM, qL, qR), Query(rs(x), xM+1, xR, qL, qR));
}
void Update(int x, int xL, int xR, int q, int num) {
    if (xL>q||xR<q) {
        return;
    }
    if (xL==xR) {
        maxn[x]=max(maxn[x], num);
        return;
    }
    int xM=(xL+xR)>>1;
    Update(ls(x), xL, xM, q, num);
    Update(rs(x), xM+1, xR, q, num);
    PushUp(x);
}
