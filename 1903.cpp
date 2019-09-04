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
void read(T&);
template<class T>
void write(const T&);

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
const int N = 133340;
const int M = 1000005;

class Query {
public:
    int l, r, t, id;
    bool operator < (const Query &i) const;
}q[N];

void add(int);
void del(int);
void modify(int, int);

int Block;
int ccnt, qcnt;
int cnt[M];
int a[N];
int ans;
int res[N];
pii chg[N];

int main () {
    int n, m;
    read(n), read(m);
    for (register int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    for (register int i = 1; i <= m; ++i) {
        char ch = getchar();
        if (ch == 'Q') {
            ++qcnt;
            read(q[qcnt].l);
            read(q[qcnt].r);
            q[qcnt].id = qcnt;
            q[qcnt].t = ccnt;
        } else {
            ++ccnt;
            read(chg[ccnt].first);
            read(chg[ccnt].second);
        }
    }
    Block = int(pow(n * 1.0 * ccnt, 0.33333));
    sort(q + 1, q + qcnt + 1);
    int l = 1, r = 0, now = 0;
    for (register int i = 1; i <= qcnt; ++i) {
        while (l > q[i].l) {
            add(a[--l]);
        }
        while (r < q[i].r) {
            add(a[++r]);
        }
        while (l < q[i].l) {
            del(a[l++]);
        }
        while (r > q[i].r) {
            del(a[r--]);
        }
        while (now < q[i].t) {
            modify(i, ++now);
        }
        while (now > q[i].t) {
            modify(i, now--);
        }
        res[q[i].id] = ans;
    }
    for (register int i = 1; i <= qcnt; ++i) {
        write(res[i]), EL;
    }
    return 0;
}

template<class T>
inline void read(T &Re) {
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
inline void write(const T &Wr) {
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

bool Query::operator < (const Query &b) const{
        return l / Block == b.l /Block ? (r / Block == b.r / Block ? t < b.t : r < b.r) : l < b.l;
}
inline void add(int x) {
    if (cnt[x]++ == 0) {
        ++ans;
    }
}
inline void del(int x) {
    if (--cnt[x] == 0) {
        --ans;
    }
}
inline void modify(int x, int ti) {
    if (chg[ti].first >= q[x].l && chg[ti].first <= q[x].r) {
        del(a[chg[ti].first]);
        add(chg[ti].second);
    }
    std::swap(a[chg[ti].first], chg[ti].second);
}
