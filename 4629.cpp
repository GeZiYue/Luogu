#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 100005;
constexpr int M = 200005;
constexpr int K = 10005;

void add(int u, int v);
void dfs(int u, int fa);

int hed[N], nxt[M], to[M], id;
int d[N], c[N];
int now[N], ans;
bool vis[N];
int dp[N][2], tmp[2][K];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(d[i]);
  }
  for (int i = 1; i <= n; ++i) {
    read(c[i]);
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  if (n > 2000) {
    for (int u = 1; u <= n; ++u) {
      if (c[u] == 1) {
        vis[u] = true;
        for (int i = hed[u]; i; i = nxt[i]) {
          int v = to[i];
          if (!vis[v]) {
            ++now[v];
          }
        }
      }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      ans += std::max(0, d[i] - now[i]);
    }
    write(ans), EL;
    return 0;
  }
  dfs(1, 0);
  write(dp[1][0]), EL;
  return 0;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs(int u, int fa) {
  int sum = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    sum += c[v];
  }
  for (int i = 0; i <= sum; ++i) {
    tmp[0][i] = iinf / 3;
  }
  tmp[0][0] = 0;
  int las = 0, now = 1;
  sum = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    for (int j = sum + c[v]; j >= 0; --j) {
      tmp[now][j] = iinf / 3;
    }
    for (int j = sum; j >= 0; --j) {
      tmp[now][j + c[v]] = std::min(tmp[now][j + c[v]], tmp[las][j] + dp[v][0]);
      tmp[now][j] = std::min(tmp[now][j], tmp[las][j] + dp[v][1]);
    }
    now ^= 1, las ^= 1;
    sum += c[v];
  }
  dp[u][0] = dp[u][1] = iinf / 3;
  for (int i = 0; i <= sum; ++i) {
    dp[u][0] = std::min(dp[u][0], tmp[las][i] + std::max(0, d[u] - i));
    dp[u][1] = std::min(dp[u][1], tmp[las][i] + std::max(0, d[u] - i - c[fa]));
  }
}

template <class T>
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
template <class T>
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
