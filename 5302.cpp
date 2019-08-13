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
const int N = 100005;
const int M = 500005;

class Point {
public:
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
    bool operator < (const Point &i) const {
        return x < i.x;
    }
}pt[M];
class Line {
public:
    int x, up, dow, val;
    Line(int _x = 0, int _u = 0, int _d = 0, int _v = 0) : x(_x), up(_u), dow(_d), val(_v) {}
    bool operator < (const Line &i) const {
        if (x == i.x) {
            return val > i.val;
        }
        return x < i.x;
    }
}ln[N << 1];

void update(int, int);
int query(int);

int cnt;
int ys[N], ye[N];
int st[N];
double high[M];
int hcnt;
bool vis[N];
int BIT[M];

int main () {
    int n, a, b, c, x0, x1;
    read(n), read(a), read(b), read(c), read(x0), read(x1);
    for (int i = 1; i <= n; ++i) {
        read(ys[i]);
    }
    for (int i = 1; i <= n; ++i) {
        read(ye[i]);
    }
    int k;
    read(k);
    for (int i = 1; i <= k; ++i) {
        int x, y, r;
        read(x), read(y), read(r);
        x = x + y;
        y = x - (y << 1);
        ln[++cnt] = Line(x - r, y + r, y - r, 1);
        ln[++cnt] = Line(x + r, y + r, y - r, -1);
    }
    int m = 0;
    for (int i = 1; i <= n; ++i) {
        st[i] = i;
    }
    for (int i = 1; i <= n; ++i) {
        int j;
        for (j = i - 1; j >= 1 && ye[i] < ye[st[j]]; --j) {
            st[j + 1] = st[j];
            double d0 = ys[i] - ys[st[j]], d1 = ye[st[j]] - ye[i];
            double x = d0 / (d0 + d1) * (x1 - x0) + x0;
            double y = d0 / (d0 + d1) * (ye[st[j]] - ys[st[j]]) + ys[st[j]];
            pt[++m] = Point(x + y, x - y);
            high[++hcnt] = x - y;
        }
        st[j + 1] = i;
    }
    sort(high + 1, high + hcnt + 1);
    hcnt = std::unique(high + 1, high + hcnt + 1) - high - 1;
    ll ans1 = a * 1ll * m;
    int num = n;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            --num;
            vis[i] = true;
            for (int j = st[i]; j != i; j = st[j]) {
                vis[j] = true;
            }
        }
    }
    ll ans2 = (a - b) * 1ll * num + m * b;
    sort(pt + 1, pt + m + 1);
    sort(ln + 1, ln + cnt + 1);
    int vs = 0;
    for (int i = 1, j = 1; i <= m; ++i) {
        while (j <= cnt && ln[j].x <= pt[i].x) {
            int l = std::lower_bound(high + 1, high + hcnt + 1, ln[j].dow) - high;
            int r = std::upper_bound(high + 1, high + hcnt + 1, ln[j].up) - high - 1;
            if (l <= r) {
                update(l, ln[j].val);
                update(r + 1, -ln[j].val);
            }
            ++j;
        }
        int x = std::lower_bound(high + 1, high + hcnt + 1, pt[i].y) - high;
        if (query(x)) {
            ++vs;
        }
    }
    ans1 += vs * 1ll * c;
    ans2 += vs * 1ll * c;
    if (ans1 > ans2) {
        std::swap(ans1, ans2);
    }
    write(ans1), SP, write(ans2), EL;
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

void update(int x, int num) {
    while (x <= 500000) {
        BIT[x] += num;
        x += (x & -x);
    }
}
int query(int x) {
    int ans = 0;
    while (x) {
        ans += BIT[x];
        x -= x & -x;
    }
    return ans;
}
