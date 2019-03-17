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
const int B = 1005;

#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)

void build(int);
bool vis(int);
void cover0(int, int);
void cover1(int, int);
void or1(int, int);
void or2(int, int);
void and1(int, int);
void and2(int, int);
void getsum(int, int);

bool a[N];
int sum[B], s01[B], s10[B];
int tag[B];
int l[B], r[B];
int bel[N];

int main () {
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

void build(int n) {
    int blocklen = int(sqrt(n));
    int m = (n - 1) / blocklen + 1;
    for (int i = 1; i <= n; ++i) {
        bel[i] = (i - 1) / blocklen + 1;
        sum[bel[i]] += a[i];
        s01[bel[i]] += !a[i - 1] & a[i];
        s10[bel[i]] += a[i] & !a[i + 1];
    }
    for (int i = 1; i <= m; ++i) {
        l[i] = r[i - 1] + 1;
        r[i] = i * blocklen;
    }
    r[m] = n;
}
bool vis(int x) {
    if (~tag[x]) {
        return tag[x];
    } else {
        return a[x];
    }
}
void cover0(int L, int R) {
    const int bl = bel[L], br = bel[R];
    if (~tag[bel[L]]) {
        for (int i = l[bl]; i <= r[bl]; ++i) {
            a[i] = tag[bl];
        }
        tag[bl] = -1;
    }
    if (a[L - 1] && a[L]) {
        ++s10[bel[L - 1]];
    }
    if (R >= r[bl]) {
        if (a[r[bl]] && a[r[bl] + 1]) {
            ++s01[bl + 1];
        }
    }
    for (int i = L; i <= min(R, r[bl]); ++i) {
        if (a[i] && !a[i + 1]) {
            --s10[bel[i]];
        }
        if (!a[i] && a[i + 1] && i != R && i != r[bl]) {
            --s01[bel[i + 1]];
        }
        if (a[i]) {
            --sum[bl];
        }
        a[i] = 0;
    }
    if (bl ^ br) {
        if (~tag[br]) {
            for (int i = l[br]; i <= r[br]; ++i) {
                a[i] = tag[br];
            }
            tag[br] = -1;
        }
        if (a[R] && a[R + 1]) {
            ++s01[bel[R + 1]];
        }
        if (a[l[br] - 1] && a[l[br]]) {
            ++s10[br - 1];
        }
        for (int i = l[br]; i <= R; ++i) {
            if (a[i] && !a[i + 1]) {
                --s10[bel[i]];
            }
            if (!a[i] && a[i + 1] && i != R) {
                --s01[bel[i + 1]];
            }
            if (a[i]) {
                --sum[br];
            }
            a[i] = 0;
        }
    }
    for (int i = bl + 1; i < br; ++i) {
        tag[i] = 0;
        sum[i] = 0;
        s01[i] = vis(l[i] - 1);
        s10[i] = vis(r[i] + 1);
    }
}
void cover0(int L, int R) {
    const int bl = bel[L], br = bel[R];
    if (~tag[bel[L]]) {
        for (int i = l[bl]; i <= r[bl]; ++i) {
            a[i] = tag[bl];
        }
        tag[bl] = -1;
    }
    if (!a[L - 1] && !a[L]) {
        ++s10[del[L - 1]];
    }
    if (R >= r[bl]) {
        if (!a[r[bl]] && !a[r[bl] + 1]) {
            ++s01[bl + 1];
        }
    }
    for (int i = L; i <= min(R, r[bl]); ++i) {
        if (!a[i] && a[i + 1]) {
            --s01[bel[i + 1]];
        }
        if (a[i] && !a[i + 1] && i != R && i != r[bl]) {
            --s10[bel[i]];
        }
        if (a[i]) {
            --sum[bl];
        }
        a[i] = 1;
    }
    if (bl ^ br) {
        if (~tag[br]) {
            for (int i = l[br]; i <= r[br]; ++i) {
                a[i] = tag[br];
            }
            tag[br] = -1;
        }
        if (a[R] && a[R + 1]) {
            ++s01[bel[R + 1]];
        }
        if (a[l[br] - 1] && a[l[br]]) {
            ++s10[br - 1];
        }
        for (int i = l[br]; i <= R; ++i) {
            if (!a[i] && a[i + 1]) {
                --s01[bel[i + 1]];
            }
            if (a[i] && !a[i + 1] && i != R) {
                --s10[bel[i]];
            }
            if (a[i]) {
                --sum[br];
            }
            a[i] = 1;
        }
    }
    for (int i = bl + 1; i < br; ++i) {
        tag[i] = 1;
        sum[i] = r[i] - l[i] + 1;
        s01[i] = !vis(l[i] - 1);
        s10[i] = !vis(r[i] + 1);
    }
}
int getsum(int L, int R) {
    const int bl = bel[L], br = bel[R];
    int ans = 0;
    for (int i = L; i <= min(R, r[br]); ++i) {
        ans += vis(i);
    }
    if (bl ^ br) {
        for (int i = l[br]; i <= R; ++i) {
            ans += vis(i);
        }
    }
    for (int i = bl + 1; i < br; ++i) {
        ans += sum[i];
    }
    return ans;
}
