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
    int id;
    int l, r;
    friend bool operator<(Query, Query);
}q[N];

int col[N];
int B;
int len, l, r;
int fz, fm;
int cnt[N];
int ans[N][2];

int gcd(int, int);
void add(int);
void del(int);

int main () {
    int n, m;
    read(n), read(m);
    B = n / sqrt(m);
    for (int i = 1; i <= n; ++i) {
        read(col[i]);
    }
    for (int i = 1; i <= m; ++i) {
        read(q[i].l), read(q[i].r);
        q[i].id = i;
    }
    sort(q + 1, q + 1 + m);

    l = 1, r = 0;
    for (int i = 1; i <= m; ++i) {
        if (q[i].l == q[i].r) {
            ans[q[i].id][0] = 0;
            ans[q[i].id][1] = 1;
            continue;
        }

        while (l > q[i].l) {
            add(--l);
        }
        while (l < q[i].l) {
            del(l++);
        }
        while (r < q[i].r) {
            add(++r);
        }
        while (r > q[i].r) {
            del(r--);
        }

        int k = gcd(fz, fm);
        ans[q[i].id][0] = fz / k;
        ans[q[i].id][1] = fm / k;
    }
    
    for (int i = 1; i <= m; ++i) {
        write(ans[i][0]), putchar('/'), write(ans[i][1]), EL;
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
    if (i.l / B == j.l / B) {
        return i.r < j.r;
    }
    return i.l < j.l;
}
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
void add(int x) {
    fz += cnt[col[x]];
    ++cnt[col[x]];
    fm += len;
    ++len;
}
void del(int x) {
    --cnt[col[x]];
    fz -= cnt[col[x]];
    --len;
    fm -= len;
}
