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
const int N = 500005;
const int M = 25;

class Node {
public:
    int i, l, r, pos, val;
    Node(int i, int l, int r, int pos, ll val) : i(i), l(l), r(r), pos(pos), val(val) {}
    bool operator < (const Node &i) const {
        return val < i.val;
    }
};

int Max(int, int);

int a[N];
int sum[N];
int maxs[N][M];
int lg2[N];
std::priority_queue<Node> pq;

int main () {
    int n, m, L, R;
    read(n), read(m), read(L), read(R);
    for (int i = 1; i <= n; ++i) {
        read(a[i]);
        maxs[i][0] = i;
        sum[i] = sum[i - 1] + a[i];
    }
    for (int i = 2; i <= n; ++i) {
        lg2[i] = lg2[i >> 1] + 1;
    }
    for (int j = 1; j <= lg2[n]; ++j) {
        for (int i = 1; i <= n - (1 << j) + 1; ++i) {
            maxs[i][j] = Max(maxs[i][j - 1], maxs[i + (1 << (j - 1))][j - 1]);
        }
    }
    for (int i = 1; i <= n - L + 1; ++i) {
        int l = i + L - 1, r = min(i + R - 1, n);
        if (l <= n) {
            int k = lg2[r - l + 1];
            int p = Max(
                maxs[l][k],
                maxs[r - (1 << k) + 1][k]
            );
            pq.push(Node(i, l, r, p, sum[p] - sum[i - 1]));
        }
    }
    ll ans = 0;
    for (int i = 1; i <= m; ++i) {
        Node now = pq.top();
        pq.pop();
        ans += now.val;
        if (now.pos ^ now.l) {
            Node l = now;
            l.r = l.pos - 1;
            int k = lg2[l.r - l.l + 1];
            int p = Max(
                maxs[l.l][k],
                maxs[l.r - (1 << k) + 1][k]
            );
            l.pos = p;
            l.val = sum[p] - sum[l.i - 1];
            pq.push(l);
        }
        if (now.pos ^ now.r) {
            Node r = now;
            r.l = r.pos + 1;
            int k = lg2[r.r - r.l + 1];
            int p = Max(
                maxs[r.l][k],
                maxs[r.r - (1 << k) + 1][k]
            );
            r.pos = p;
            r.val = sum[p] - sum[r.i - 1];
            pq.push(r);
        }
    }
    write(ans), EL;
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

int Max(int x, int y) {
    return sum[x] > sum[y] ? x : y;
}
