#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 100005
#define ll long long int
#define File(a) freopen(a".in", "r", stdin) , freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
ll sqr(ll);
class Seg_Tree {
private:
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
    ll sum[4 * N], maxn[4 * N];
public:
    void Push_Up(int);
    void Build(int, int, int);
    ll Query(int, int, int, int, int);
    void Update(int, int, int, int, int);
}T;
ll a[N];
int main () {
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    T.Build(1, 1, n);
    int m;
    read(m);
    for (int i = 1; i <= m ; i++) {
        int k , l , r;
        read(k);
        read(l);
        read(r);
        if (l > r) {
            swap(l, r);
        }
        if (k == 0) {
            T.Update(1, 1, n, l, r);
        }else {
            write(T.Query(1, 1, n, l, r));
            EL;
        }
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k = 0;
    char ch = getchar();
    int flag = 1;
    while(!isNum(ch) ) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while(isNum(ch) ) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e < 0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e < 10) {
            putchar(w_r_i_t_e + '0');
        }else {
            write(w_r_i_t_e / 10);
            putchar( (w_r_i_t_e % 10) + '0');
        }
    }
}
ll sqr(ll x) {
    return int(sqrt(x * 1.0));
}
void Seg_Tree::Push_Up(int x) {
    sum[x] = sum[ls(x)] + sum[rs(x)];
    maxn[x] = max(maxn[ls(x)], maxn[rs(x)]);
}
void Seg_Tree::Build(int x, int xL, int xR) {
    if (xL == xR) {
        sum[x] = maxn[x] = a[xL];
        return;
    }
    int xM = (xL + xR) >> 1;
    Build(ls(x), xL, xM);
    Build(rs(x), xM + 1, xR);
    Push_Up(x);
}
ll Seg_Tree::Query(int x, int xL, int xR, int qL, int qR) {
    if (xL >= qL && xR <= qR) {
        return sum[x];
    }
    if (xR < qL || xL > qR) {
        return 0;
    }
    int xM = (xL + xR) >> 1;
    return Query(ls(x), xL, xM, qL, qR) +
           Query(rs(x), xM + 1, xR, qL, qR);
}
void Seg_Tree::Update(int x, int xL, int xR, int uL, int uR) {
    if (xR < uL || xL > uR) {
        return;
    }
    if (xL == xR) {
        sum[x] = maxn[x] = sqr(sum[x]);
        return;
    }
    if (maxn[x] == 1) {
        return;
    }
    int xM = (xL + xR) >> 1;
    Update(ls(x), xL, xM, uL, uR);
    Update(rs(x), xM + 1, xR, uL, uR);
    Push_Up(x);
}
