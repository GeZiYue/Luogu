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

constexpr int N = 5005;
constexpr int Mod = 998244353;

void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
int C(int n, int m);
int pow(int a, int b, int m);
void add(int u, int v);
void dfs(int u, int fa);

int hed[N], nxt[N << 1], to[N << 1], id;
int fac[N], ifac[N], inv[N];
int dp[N][N][3];
int tmp[N][3];
int Tmp[N];
int siz[N];
int Ans[N], deg;
int now[N], cnt[N];
int n, m;

int main() {
  fac[0] = 1;
  for (int i = 1; i <= 5000; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % Mod;
  }
  ifac[5000] = pow(fac[5000], Mod - 2, Mod);
  for (int i = 4999; i >= 0; --i) {
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % Mod;
  }
  read(n);
  Ans[0] = 1;
  while (n--) {
    id = 0;
    for (int i = 1; i <= m; ++i) {
      hed[i] = 0;
    }
    read(m);
    for (int i = 1; i < m; ++i) {
      int u, v;
      read(u), read(v);
      add(u, v), add(v, u);
    }
    for (int i = 1; i <= m; ++i) {
      memset(dp[i], 0, sizeof(dp[i]));
    }
    dfs(1, 0);
    for (int i = 0; i <= m; ++i) {
      cnt[i] = 1ll * dp[1][i][2] * fac[i] % Mod;
    }
    for (int i = 0; i <= m; ++i) {
      now[i] = 0;
      for (int j = i; j <= m; ++j) {
        if ((i ^ j) & 1) {
          dec(now[i], 1ll * cnt[j] * C(j - 1, i - 1) % Mod);
        } else {
          inc(now[i], 1ll * cnt[j] * C(j - 1, i - 1) % Mod);
        }
      }
      now[i] = 1ll * now[i] * ifac[i] % Mod;
    }
    for (int i = 0; i <= deg + m; ++i) {
      Tmp[i] = 0;
    }
    for (int i = 0; i <= deg; ++i) {
      for (int j = 0; j <= m; ++j) {
        inc(Tmp[i + j], 1ll * Ans[i] * now[j] % Mod);
      }
    }
    deg += m;
    for (int i = 0; i <= deg; ++i) {
      Ans[i] = Tmp[i];
    }
  }
  int ans = 0;
  for (int i = 0; i < deg; ++i) {
    inc(ans, 1ll * Ans[i + 1] * fac[i] % Mod);
  }
  write(ans), EL;
  return 0;
}

int C(int n, int m) { return 1ll * fac[n] * ifac[m] % Mod * ifac[n - m] % Mod; }
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
void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
}
void dfs(int u, int fa) {
  dp[u][0][0] = dp[u][0][1] = dp[u][1][2] = 1;
  dp[u][0][2] = dp[u][1][0] = dp[u][1][1] = 0;
  siz[u] = 1;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v == fa) {
      continue;
    }
    dfs(v, u);
    for (int j = 0; j <= siz[u] + siz[v]; ++j) {
      tmp[j][0] = tmp[j][1] = tmp[j][2] = 0;
    }
    for (int j = 0; j <= siz[u]; ++j) {
      for (int k = 0; k <= siz[v]; ++k) {
#define upd(x, y, z) inc(tmp[j + k][x], 1ll * dp[u][j][y] * dp[v][k][z] % Mod)
        upd(0, 0, 2), upd(1, 1, 2), upd(2, 2, 2), upd(1, 0, 1);
        inc(tmp[j + k + 1][2], 2ll * dp[u][j][1] * dp[v][k][1] % Mod);
      }
    }
    siz[u] += siz[v];
    for (int j = 0; j <= siz[u]; ++j) {
      dp[u][j][0] = tmp[j][0], dp[u][j][1] = tmp[j][1], dp[u][j][2] = tmp[j][2];
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
