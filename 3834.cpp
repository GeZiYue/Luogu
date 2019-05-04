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
const int N = 200005;

class Node {
public:
    int val;
    int ls, rs;
} tree[N * 20];
int cnt;

void insert(int&, int, int, int);
int query(int, int, int, int, int);

pii a[N];
int rnk[N];
int root[N];

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
        read(a[i].first);
        a[i].second = i;
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++i) {
        rnk[a[i].second] = i;
    }
    for (int i = 1; i <= n; ++i) {
        root[i] = root[i - 1];
        insert(root[i], 1, n, rnk[i]);
    }
    for (int i = 1; i <= m; ++i) {
        int l, r, k;
        read(l), read(r), read(k);
        write(a[query(root[l - 1], root[r], 1, n, k)].first), EL;
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

void insert(int &x, int xl, int xr, int ins) {
    tree[++cnt]=tree[x];
    x = cnt;
    ++tree[x].val;
    if (xl == xr) {
        return;
    }
    int xm = (xl + xr) >> 1;
    if (ins <= xm) {
        insert(tree[x].ls, xl, xm, ins);
    } else {
        insert(tree[x].rs, xm + 1, xr, ins);
    }
}
int query(int lx, int rx, int xl, int xr, int k) {
    if (xl == xr) {
        return xl;
    }
    int xm = (xl + xr) >> 1;
    int now = tree[tree[rx].ls].val - tree[tree[lx].ls].val;
    if (k <= now) {
        return query(tree[lx].ls, tree[rx].ls, xl, xm, k);
    } else {
        return query(tree[lx].rs, tree[rx].rs, xm + 1, xr, k - now);
    }
}
