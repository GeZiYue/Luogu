#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 100005;

void dfs(int u);

int vis[N];
std::vector<std::pair<int, bool> > G[N];
int a[N];
ll sum;
bool flag;
int n, m;

int main() {
  int T;
  read(T);
  while (T--) {
    read(n), read(m);
    for (int i = 1; i <= n; ++i) {
      read(a[i]);
      G[i].clear();
    }
    for (int i = 1; i <= n; ++i) {
      int x;
      read(x);
      a[i] -= x;
    }
    for (int i = 1; i <= m; ++i) {
      int k, u, v;
      read(k), read(u), read(v);
      G[u].emplace_back(v, k & 1);
      G[v].emplace_back(u, k & 1);
    }
    std::fill(vis + 1, vis + n + 1, -1);
    bool ans = true;
    for (int i = 1; i <= n; ++i) {
      if (vis[i] == -1) {
        vis[i] = 0;
        sum = 0, flag = true;
        dfs(i);
        if (flag) {
          ans &= (sum == 0);
        } else {
          ans &= (sum % 2 == 0);
        }
      }
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}

void dfs(int u) {
  if (vis[u]) {
    sum += a[u];
  } else {
    sum -= a[u];
  }
  for (auto edge : G[u]) {
    int v = edge.first;
    bool w = edge.second;
    if (~vis[v]) {
      if (vis[v] != (vis[u] ^ w)) {
        flag = false;
      }
    } else {
      vis[v] = vis[u] ^ w;
      dfs(v);
    }
  }
}

template <typename T>
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
template <typename T>
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
