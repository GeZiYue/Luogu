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

constexpr int N = 300005;
constexpr int M = 600005;
typedef std::pair<ll, int> pr;

void upd(pr &x, pr y) { (x < y) ? (x = y, void()) : void(); }
pr operator+(const pr &x, const pr &y) { return {x.first + y.first, x.second + y.second}; }
void add(int u, int v, int w);
void dfs(int u, int fa);

int hed[N], nxt[M], to[M], dis[M], id;
pr dp[N][3];
ll val;
int n, k;

int main() {
  read(n), read(k);
  ++k;
  for (int i = 1; i < n; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    add(u, v, w), add(v, u, w);
  }
  ll l = -1e12, r = 1e12;
  ll ans = 0;
  while (l <= r) {
    val = (l + r) >> 1;
    dfs(1, 0);
    pr t = std::max({dp[1][0], dp[1][1], dp[1][2]});
    if (t.second < k) {
      l = val + 1;
    } else {
      r = val - 1;
      ans = t.first - val * k;
    }
  }
  write(ans), EL;
  return 0;
}

void add(int u, int v, int w) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
  dis[id] = w;
}
void dfs(int u, int fa) {
  dp[u][0] = {0, 0}, dp[u][1] = {(ll)-1e12, 0}, dp[u][2] = {val, 1};
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    pr t = std::max({dp[v][0], dp[v][1], dp[v][2]});
    upd(dp[u][2], dp[u][2] + t);
    upd(dp[u][2], dp[u][1] + dp[v][0] + pr(dis[i], 0));
    upd(dp[u][2], dp[u][1] + dp[v][1] + pr(dis[i] - val, -1));
    upd(dp[u][1], dp[u][1] + t);
    upd(dp[u][1], dp[u][0] + dp[v][1] + pr(dis[i], 0));
    upd(dp[u][1], dp[u][0] + dp[v][0] + pr(dis[i] + val, 1));
    upd(dp[u][0], dp[u][0] + t);
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
