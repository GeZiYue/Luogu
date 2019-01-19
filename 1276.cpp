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
#define N 50005
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
class SegmentTree {
public:
    int sum[N];
    int tag[N];
    int cnt;
    void PushUp(int);
    void PushDown(int, int, int);
    void Build(int, int, int);
    void Plant(int, int, int, int, int);
    void Remove(int, int, int, int, int);
}t1, t2;
int main () {
    int n, m;
    read(n, m);
    ++n;
    t1.Build(1, 1, n);
    t2.Build(1, 1, n);
    for (int i=1; i<=m; ++i) {
        int mod, l, r;
        read(mod, l, r);
        ++l, ++r;
        if (mod) {
            t1.Plant(1, 1, n, l, r);
        }else {
            t1.Remove(1, 1, n, l, r);
            t2.Remove(1, 1, n, l, r);
        }
    }
    write(t1.sum[1]-t2.sum[1]);EL;
    write(t1.cnt-t2.cnt);EL;
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
void SegmentTree::PushUp(int x) {
    sum[x]=sum[ls(x)]+sum[rs(x)];
}
void SegmentTree::PushDown(int x, int xL, int xR) {
    if (tag[x]==1) {
        int xM=(xL+xR)>>1;
        sum[ls(x)]=xM-xL+1;
        sum[rs(x)]=xR-xM;
        tag[ls(x)]=tag[rs(x)]=1;
    }
    if (tag[x]==-1) {
        sum[ls(x)]=sum[rs(x)]=0;
        tag[ls(x)]=tag[rs(x)]=-1;
    }
    tag[x]=0;
}
void SegmentTree::Build(int x, int xL, int xR) {
    if (xL==xR) {
        sum[x]=1;
        return;
    }
    int xM=(xL+xR)>>1;
    Build(ls(x), xL, xM);
    Build(rs(x), xM+1, xR);
    PushUp(x);
}
void SegmentTree::Plant(int x, int xL, int xR, int uL, int uR) {
    if (xL>=uL&&xR<=uR) {
        sum[x]=xR-xL+1;
        tag[x]=1;
        return;
    }
    if (xL>uR||xR<uL) {
        return;
    }
    PushDown(x, xL, xR);
    int xM=(xL+xR)>>1;
    Plant(ls(x), xL, xM, uL, uR);
    Plant(rs(x), xM+1, xR, uL, uR);
    PushUp(x);
}
void SegmentTree::Remove(int x, int xL, int xR, int uL, int uR) {
    if (xL>=uL&&xR<=uR) {
        cnt+=sum[x];
        sum[x]=0;
        tag[x]=-1;
        return;
    }
    if (xL>uR||xR<uL) {
        return;
    }
    PushDown(x, xL, xR);
    int xM=(xL+xR)>>1;
    Remove(ls(x), xL, xM, uL, uR);
    Remove(rs(x), xM+1, xR, uL, uR);
    PushUp(x);
}
