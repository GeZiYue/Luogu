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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 1000005;

void build(int&, int, int);
void update(int&, int, int, int, int);
int query(int, int, int, int);

class Node {
public:
    int val, ls, rs;
}tree[N * 20];

int cnt;
int root[N];
int a[N];

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    build(root[0], 1, n);
    for (int i = 1; i <= m; ++i) {
        int v, op, x;
        read(v), read(op), read(x);
        if (op == 1) {
            int u;
            read(u);
            root[i] = root[v];
            update(root[i], 1, n, x, u);
        } else {
            write(query(root[v], 1, n, x)), EL;
            root[i] = root[v];
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
        tree[x].val = a[xl];
        return;
    }
    int xm = (xl + xr) >> 1;
    build(tree[x].ls, xl, xm);
    build(tree[x].rs, xm + 1, xr);
}
void update(int &x, int xl, int xr, int ux, int num) {
    tree[++cnt] = tree[x];
    x = cnt;
    if (xl == xr) {
        tree[x].val = num;
        return;
    }
    int xm = (xl + xr) >> 1;
    if (ux <= xm) {
        update(tree[x].ls, xl, xm, ux, num);
    } else {
        update(tree[x].rs, xm + 1, xr, ux, num);
    }
}
int query(int x, int xl, int xr, int qx) {
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
