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

constexpr int N = 1005;
constexpr int Mod = 998244353;

void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
int pow(int a, int b, int m);
void add(int u, int v);
void dfs(int u, int fa);

int dp[N][N * 3], tmp[N * 3];
int hed[N], nxt[N * 2], to[N * 2], id;
int siz[N];
int inv[N * 3];
int p[N][3];
int n;

int main() {
  read(n);
  inv[1] = 1;
  for (int i = 2; i <= n * 3; ++i) {
    inv[i] = 1ll * (Mod - Mod / i) * inv[Mod % i] % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    int a, b, c;
    read(a), read(b), read(c);
    int s = pow(a + b + c, Mod - 2, Mod);
    p[i][0] = 1ll * a * s % Mod, p[i][1] = 1ll * b * s % Mod, p[i][2] = 1ll * c * s % Mod;
  }
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  dfs(1, 0);
  int ans = 0;
  for (int i = 1; i <= siz[1]; ++i) {
    inc(ans, dp[1][i]);
  }
  write(ans), EL;
  return 0;
}

void dfs(int u, int fa) {
  siz[u] = 3;
  for (int i = 1; i <= 3; ++i) {
    dp[u][i] = 1ll * i * p[u][i - 1] % Mod;
  }
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    for (int j = 0; j <= siz[u] + siz[v]; ++j) {
      tmp[j] = 0;
    }
    for (int j = 0; j <= siz[u]; ++j) {
      for (int k = 0; k <= siz[v]; ++k) {
        int qwq = 1ll * dp[u][j] * dp[v][k] % Mod;
        if (i & 1) {
          inc(tmp[j + k], qwq);
        } else {
          dec(tmp[j + k], qwq);
          inc(tmp[j], qwq);
        }
      }
    }
    siz[u] += siz[v];
    for (int j = 0; j <= siz[u]; ++j) {
      dp[u][j] = tmp[j];
    }
  }
  for (int i = 1; i <= siz[u]; ++i) {
    dp[u][i] = 1ll * dp[u][i] * inv[i] % Mod;
  }
}
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = 1ll * ans * now % m;
    }
    now = 1ll * now * now % m;
    b >>= 1;
  }
  return ans;
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
