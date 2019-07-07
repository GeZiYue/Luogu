#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
inline void read(T&);
template<class T>
inline void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const int& ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 100005;
const int M = 200005;

class Node {
public:
    int ls, rs;
    pii val;
} tree[N * 20];
int cnt;

void build(int&, int, int);
pii query(int, int, int, int);
void update(int&, int, int, int, int);
void add(int, int, int, int);
pii find(int, int);
void uni(int, int, int);
int chk(int, int, int);

int root[M];
int n, m;

int main () {
    read(n), read(m);
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int mod;
        read(mod);
        if (mod == 1) {
            int a, b;
            read(a), read(b);
            uni(i - 1, a, b);
        } else {
            if (mod == 2) {
                int a;
                read(a);
                root[i] = root[a];
            } else {
                int a, b;
                read(a), read(b);
                write(chk(i - 1, a, b)), EL;
            }
        }
    }
    return 0;
}

template<class T>
void read(T &Re) {
    T k = 0;
    char ch = getchar();
    int flag = 1;
    while (!isNum(ch)) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while (isNum(ch)) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    Re = flag * k;
}
template<class T>
void write(const T &Wr) {
    if (Wr < 0) {
        putchar('-');
        write(-Wr);
    } else {
        if (Wr < 10) {
            putchar(Wr + '0');
        } else {
            write(Wr / 10);
            putchar((Wr % 10) + '0');
        }
    }
}

void build(int &x, int xl, int xr) {
    x = ++cnt;
    if (xl == xr) {
        tree[x].val.first = xl;
        tree[x].val.second = 0;
        return;
    }
    int xm = (xl + xr) >> 1;
    build(tree[x].ls, xl, xm), build(tree[x].rs, xm + 1, xr);
}
pii query(int x, int xl, int xr, int qx) {
    if (xl == xr) {
        return tree[x].val;
    }
    int xm = (xl + xr) >> 1;
    if (qx <= xm) {
        return query(tree[x].ls, xl, xm, qx);
    } else {
        return query(tree[x].rs, xm + 1, xr, qx);
    }
}
void update(int &x, int xl, int xr, int ux, int u) {
    tree[++cnt] = tree[x];
    x = cnt;
    if (xl == xr) {
        tree[x].val.first = u;
        return;
    }
    int xm = (xl + xr) >> 1;
    if (ux <= xm) {
        update(tree[x].ls, xl, xm, ux, u);
    } else {
        update(tree[x].rs, xm + 1, xr, ux, u);
    }
}
void add(int x, int xl, int xr, int ax) {
    if (xl == xr) {
        ++tree[x].val.second;
        return;
    }
    int xm = (xl + xr) >> 1;
    if (ax <= xm) {
        add(tree[x].ls, xl, xm, ax);
    } else {
        add(tree[x].rs, xm + 1, xr, ax);
    }
}
pii find(int rt, int x) {
    pii q = query(root[rt], 1, n, x);
    if (q.first == x) {
        return q;
    } else {
        return find(rt, q.first);
    }
}
void uni(int rt, int a, int b) {
    pii fa = find(rt, a), fb = find(rt, b);
    root[rt + 1] = root[rt];
    if (fa.first ^ fb.first) {
        if (fa.second > fb.second) {
            update(root[rt + 1], 1, n, fb.first, fa.first);
        } else {
            if (fa.second < fb.second) {
                update(root[rt + 1], 1, n, fa.first, fb.first);
            } else {
                update(root[rt + 1], 1, n, fa.first, fb.first);
                add(root[rt + 1], 1, n, fb.first);
            }
        }
    }
}
int chk(int rt, int a, int b) {
    root[rt + 1] = root[rt];
    int fa = find(rt, a).first, fb = find(rt, b).first;
    return fa == fb;
}
