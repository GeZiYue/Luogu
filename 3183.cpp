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
const int N = 100005;
const int M = 200005;

void add(int, int);

int hed[N], nxt[M], to[M], id;
int deg[N];
int sum[N];
bool vis[N];
bool lon[N];
std::queue<int> q;

int main () {
    int n, m;
    read(n), read(m);
    for (int i = 1; i <= m; ++i) {
        int u, v;
        read(u), read(v);
        add(u, v);
        ++deg[v];
    }
    for (int i = 1; i <= n; ++i) {
        if (!deg[i]) {
            sum[i] = 1;
            vis[i] = true;
            lon[i] = true;
            q.push(i);
        }
    }
    int ans = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = to[i];
            if (!vis[v]) {
                sum[v] += sum[u];
                --deg[v];
                if (!deg[v]) {
                    q.push(v);
                }
            }
        }
        if (!hed[u] && !lon[u]) {
            ans += sum[u];
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

void add(int u, int v) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
}
