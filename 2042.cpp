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
const int N = 4000005;
#define lc(x) ch[x][0]
#define rc(x) ch[x][1]

int fa[N], ch[N][2];
int num[N], siz[N];
int sm[N], ml[N], mr[N];
bool rev[N], chg[N];
int id, root;

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

void reverse(int x) {
    lc(x) ^= rc(x) ^= lc(x) ^= rc(x);
    rev[x] ^= 1;
}
void pushup(int x) {
    sm[x] = sm[lc(x)] + sm[rc(x)];
    siz[x] = siz[lc(x)] + siz[rc(x)];
    ml[x] = max(ml[lc(x)], sm[lc(x)] + ml[rc(x)]);
    mr[x] = max(mr[rc(x)], sm[rc(x)] + mr[lc(x)]);
}
void pushdown(int x) {
    if (rev[x]) {
        reverse(lc(x)), reverse(rc(x));
        rev[x] = false;
    }
    if (chg[x]) {
        num[lc(x)] = num[rc(x)] = num[x];
        sm[lc(x)] = num[x] * siz[lc(x)];
        ml[lc(x)] = mr[lc(x)] = max(sm[lc(x)], 0);
        sm[rc(x)] = num[x] * siz[rc(x)];
        ml[rc(x)] = mr[rc(x)] = max(sm[rc(x)], 0);
        chg[lc(x)] = chg[rc(x)] = true;
        chg[x] = false;
    }
}
bool getid(int x) {
    return rc(fa[x]) == x;
}
void connect(int x, int f, int how) {
    ch[f][how] = x;
    fa[x] = f;
}
void rotate(int x) {
    int y = fa[x], z = fa[x];
    bool ys = getid(x), zs = getid(y);
    connect(ch[x][ys ^ 1], y, ys);
    connect(y, x, ys ^ 1);
    connect(x, z, zs);
}
void splay(int x, int to) {
    while (fa[x] ^ to) {
        if (fa[fa[x]] ^ to) {
            rotate(getid(x) ^ getid(fa[x]) ? x : fa[x]);
        }
        rotate(x);
    }
    if (!to) {
        root = x;
    }
}
int find(int k) {
    int now = root;
    while (true) {
        pushdown(now);
        int num = siz[lc(now)] + 1;
        if (num == k) {
            return now;
        }
        if (num > k) {
            now = lc(now);
        } else {
            now = rc(now);
            k -= num;
        }
    }
}
