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
const int N = 4500005;
const int M = 500005;

void insert(int, int, int*);
void del(int, int);
void upd(int, int, int);
void reverse(int, int);
int getsum(int, int);
int getmax();

int ch[N][2], val[N], fa[N], siz[N], sm[N], sl[N], sr[N], st[N], tagc[N];
bool tagr[N];
int a[M];
int root, cnt;

int main () {
    int n, m;
    read(n), read(m);
    fa[2] = siz[2] = root = 1;
    ch[1][1] = siz[1] = cnt = 2;
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
    }
    insert(0, n, a);
    for (int i = 1; i <= m; ++i) {
        std::string str;
        std::cin >> str;
        if (str[2] == 'X') {
            write(getmax()), EL;
            continue;
        }
        int pos, n;
        read(pos), read(n);
        if (str[0] == 'I') {
            for (int j = 1; j <= n; ++j) {
                read(a[j]);
            }
            insert(pos, n, a);
        } else {
            if (str[0] == 'D') {
                del(pos, n);
            } else {
                if (str[0] == 'M') {
                    int num;
                    read(num);
                    upd(pos, n, num);
                } else {
                    if (str[0] == 'R') {
                        reverse(pos, n);
                    } else {
                        write(getsum(pos, n)), EL;
                    }
                }
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

void swap(int &a, int &b) {
    a ^= b ^= a ^= b;
}
void pushup(int x) {
    siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1;
    sm[x] = sm[ch[x][0]] + sm[ch[x][1]] + val[x];
    sl[x] = max(sl[ch[x][0]], sm[ch[x][0]] + val[x] + sl[ch[x][1]]);
    sr[x] = max(sr[ch[x][1]], sm[ch[x][1]] + val[x] + sr[ch[x][0]]);
    st[x] = max(max(st[ch[x][0]], st[ch[x][1]]), sr[ch[x][0]] + val[x] + sl[ch[x][1]]);
}
void rev(int x) {
    swap(ch[x][0], ch[x][1]);
    swap(sl[x], sr[x]);
}
void chg(int x, int num) {
    tagc[x] = num;
    tagr[x] = false;
    sl[x] = sr[x] = st[x] = max(0, sm[x] = num * siz[x]);
}
void pushdown(int x) {
    if (tagc[x] != -iinf) {
        if (ch[x][0]) {
            chg(ch[x][0], tagc[x]);
        }
        if (ch[x][1]) {
            chg(ch[x][1], tagc[x]);
        }
        tagc[x] = -iinf;
    }
    if (tagr[x]) {
        if (ch[x][0]) {
            rev(ch[x][0]);
        }
        if (ch[x][1]) {
            rev(ch[x][1]);
        }
        tagr[x] = 0;
    }
}
bool getid(int x) {
    return ch[fa[x]][1] == x;
}
void connect(int x, int f, int how) {
    fa[x] = f;
    if (f ^ 0) {
        ch[f][how] = x;
    }
}
void rotate(int x) {
    int y = fa[x], r = fa[y], ys = getid(x), rs = getid(y);
    connect(ch[x][ys ^ 1], y, ys);
    connect(y, x, ys ^ 1);
    connect(x, r, rs);
    pushup(x), pushup(y);
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
        write(now), SP, write(ch[now][0]), SP, write(siz[ch[now][0]]), SP, write(k), EL;
        int num = siz[ch[now][0]] + 1;
        if (num == k) {
            return now;
        }
        if (num < k) {
            k -= num;
            now = ch[now][1];
        } else {
            now = ch[now][0];
        }
    }
}
int build(int xl, int xr, int f, int *num) {
    if (xl > xr) {
        return 0;
    }
    int xm = (xl + xr) >> 1;
    int now = ++cnt;
    siz[now] = xr - xl + 1;
    val[now] = num[xm];
    fa[now] = f;
    ch[now][0] = build(xl, xm - 1, now, num);
    ch[now][1] = build(xm + 1, xr, now, num);
    pushup(now);
    write(now), SP, write(val[now]), SP, write(xl), SP, write(xr), SP, write(sm[now]), SP, write(siz[now]), EL;
    return now;
}
void insert(int x, int n, int *num) {
    int l = find(x + 1), r = find(x + 2);
    splay(l, 0), splay(r, l);
    fa[ch[r][0] = build(1, n, 0, num)] = r;
    pushup(r), pushup(l);
}
void del(int x, int n) {
    int l = find(x), r = find(x + n + 1);
    splay(l, 0), splay(r, l);
    ch[r][0] = fa[ch[r][0]] = 0;
    pushup(r), pushup(l);
}
void upd(int x, int n, int num) {
    int l = find(x), r = find(x + n + 1);
    splay(l, 0), splay(r, l);
    chg(ch[r][0], num);
}
void reverse(int x, int n) {
    int l = find(x), r = find(x + n + 1);
    splay(l, 0), splay(r, l);
    rev(ch[r][0]);
}
int getsum(int x, int n) {
    int l = find(x), r = find(x + n + 1);
    splay(l, 0), splay(r, l);
    write(l), SP, write(r), SP, write(ch[r][0]), SP, write(siz[ch[r][0]]), EL;
    return sm[ch[r][0]];
}
int getmax() {
    int l = 1, r = 2;
    splay(l, 0), splay(r, l);
    return st[ch[r][0]];
}
