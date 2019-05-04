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
const int N = 50005;

class Query {
public:
    int id, l, r;
    friend bool operator<(Query, Query);
}q[N];

void add(int);
void del(int);

int col[N];
int cnt[N];
int ans[N];
int B;
int len, now;

int main () {
    int n, m, k;
    read(n), read(m), read(k);
    B = n / sqrt(m);
    for (int i = 1; i <= n; ++i) {
        read(col[i]);
    }
    for (int i = 1; i <= m; ++i) {
        q[i].id = i;
        read(q[i].l), read(q[i].r);
    }
    sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        while (l > q[i].l) {
            add(--l);
        }
        while (l < q[i].l) {
            del(l++);
        }
        while (r > q[i].r) {
            del(r--);
        }
        while (r < q[i].r) {
            add(++r);
        }
        ans[q[i].id] = now;
    }
    for (int i = 1; i <= m; ++i) {
        write(ans[i]), EL;
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

bool operator<(Query i, Query j) {
    return i.l / B == j.l / B ? i.r < j.r : i.l < j.l;
}
void add(int x) {
    now += 2 * cnt[col[x]] + 1;
    ++cnt[col[x]];
    ++len;
}
void del(int x) {
    now -= 2 * cnt[col[x]] - 1;
    --cnt[col[x]];
    --len;
}
