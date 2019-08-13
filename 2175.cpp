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
const int N = 2005;
const int M = 8000005;

void add(int, int);
void dfs(int);

int col[N];
int hed[N], nxt[M], to[M], id;
bool dp[2][N << 1];
int lik[N];
int sum[2];

int main () {
    int n;
    read(n);
    int a;
    for (int i = 1; i <= n; ++i) {
        col[i] = -1;
        while (1) {
            read(a);
            if (a == 0) {
                break;
            }
            lik[a] = true;
        }
        for (int j = 1; j <= n; ++j) {
            if (i != j && !lik[j]) {
                add(i, j);
                add(j, i);
            }
            lik[j] = false;
        }
    }
    bool now = 0;
    dp[0][2001] = true;
    for (int i = 1; i <= n; ++i) {
        if (col[i] == -1) {
            now ^= 1;
            col[i] = 0;
            sum[0] = sum[1] = 0;
            dfs(i);
            for (int j = n; j >= -n; --j) {
                dp[now][j + 2001] = dp[now ^ 1][j - sum[0] + sum[1] + 2001] || dp[now ^ 1][j + sum[0] - sum[1] + 2001];
            }
        }
    }
    int ans = 0;
    for (int i = -n; i <= n; ++i) {
        if (dp[now][i + 2001]) {
            a = (n + i) / 2;
            if ((a << 1) > n) {
                a = n - a;
            }
            ans = max(ans, a);
        }
    }
    write(ans), SP, write(n - ans), EL;
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
void dfs(int u) {
    ++sum[col[u]];
    int v;
    for (int i = hed[u]; i; i = nxt[i]) {
        v = to[i];
        if (col[v] == -1) {
            col[v] = col[u] ^ 1;
            dfs(v);
        } else {
            if (col[v] == col[u]) {
                puts("No solution");
                exit(0);
            }
        }
    }
}
