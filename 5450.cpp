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

const int N = 530000;
const int Mod = 998244353, g = 3, iv2 = (Mod + 1) / 2;

typedef std::vector<int> Poly;

int pow(int a, int b, int m);
int add(int a, int b) { return (a += b) >= Mod ? a -= Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a += Mod : a; }

namespace Pol {
void getr(int lim);
void init_Poly();
void NTT(Poly &A, int lim, bool flag);
Poly inv(Poly A, int n);
Poly mult(Poly A, int n, Poly B, int m);
Poly Tmul(Poly A, int n, Poly B, int m);
void getv(const Poly &A, int n, int *f, int *ans, int m);
Poly G[N << 1];
ull tmp[N];
int gw[N];
int r[N];
}  // namespace Pol

Poly solve(int xl, int xr);
void dfs(int u);

int ans[N];
std::vector<int> G[N];
std::vector<int> cir;
bool vis[N];
int fa[N], siz[N];
int al[N], s[N];
int iv[N];
int n, a, b;

int main() {
  Pol::init_Poly();
  read(n), read(a), read(b);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    G[u].push_back(v), G[v].push_back(u);
  }
  int fac = 1;
  for (int i = 1; i <= n; ++i) fac = 1ll * fac * i % Mod;
  iv[1] = 1;
  for (int i = 2; i <= n; ++i) iv[i] = 1ll * (Mod - Mod / i) * iv[Mod % i] % Mod;
  dfs(a);
  for (int x = b; x; x = fa[x]) cir.push_back(x), vis[x] = true;
  cir.push_back(0);
  std::reverse(cir.begin(), cir.end());
  int sz = cir.size() - 1;
  for (int i = 1; i <= sz; ++i) {
    int u = cir[i];
    dfs(u);
    al[i] = siz[u];
  }
  for (int i = 1; i <= sz; ++i) s[i] = (s[i - 1] + al[i]) % Mod;
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) fac = 1ll * fac * iv[siz[i]] % Mod;
  }
  Poly p = solve(0, sz);
  for (int i = 0; i <= sz; ++i) p[i] = 1ll * p[i + 1] * (i + 1) % Mod;
  p[sz + 1] = 0;
  Pol::getv(p, sz, s, ans, sz + 1);
  int sum = 0;
  fac = 1ll * iv2 * fac % Mod;
  for (int i = 0, now = Mod - 1; i <= sz; ++i, now = Mod - now) {
    sum = add(sum, 1ll * now * fac % Mod * pow(ans[i], Mod - 2, Mod) % Mod);
  }
  write(sum), EL;
  return 0;
}

void dfs(int u) {
  siz[u] = 1;
  for (int v : G[u]) {
    if (v == fa[u] || vis[v]) continue;
    fa[v] = u;
    dfs(v);
    siz[u] += siz[v];
  }
}
Poly solve(int xl, int xr) {
  if (xl == xr) {
    return Poly{s[xl], Mod - 1};
  }
  int xm = (xl + xr) >> 1;
  return Pol::mult(solve(xl, xm), xm - xl + 2, solve(xm + 1, xr), xr - xm + 1);
}

namespace Pol {
void NTT(Poly &A, int lim, bool flag) {
  for (int i = 0; i < lim; ++i) tmp[i] = A[i];
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) std::swap(tmp[i], tmp[r[i]]);
  }
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        ull x = tmp[i | j], y = tmp[i | j | l] * gw[l | j] % Mod;
        tmp[i | j] = x + y, tmp[i | j | l] = x + Mod - y;
      }
    }
  }
  if (flag) {
    std::reverse(tmp + 1, tmp + lim);
    int iv = pow(lim, Mod - 2, Mod);
    for (int i = 0; i < lim; ++i) tmp[i] = tmp[i] * iv % Mod;
  }
  for (int i = 0; i < lim; ++i) A[i] = tmp[i] % Mod;
}
Poly inv(Poly A, int n) {
  int lim = 1;
  while (lim < (n << 1)) lim <<= 1;
  Poly F(lim), G(lim);
  A.resize(lim);
  G[0] = pow(A[0], Mod - 2, Mod);
  int now = 1;
  while (now < n) {
    std::copy_n(A.begin(), now << 1, F.begin());
    int lim = now << 2;
    getr(lim);
    NTT(G, lim, false), NTT(F, lim, false);
    for (int i = 0; i < lim; ++i) G[i] = 1ll * sub(2, 1ll * G[i] * F[i] % Mod) * G[i] % Mod;
    NTT(G, lim, true);
    std::fill_n(G.begin() + (now << 1), now << 1, 0);
    now <<= 1;
  }
  G.resize(n);
  return G;
}
Poly mult(Poly A, int n, Poly B, int m) {
  if (1ll * n * m < 64) {
    Poly ans(n + m - 1);
    std::fill(tmp, tmp + n + m, 0);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) tmp[i + j] += 1ll * A[i] * B[j] % Mod;
    for (int i = 0; i < n + m - 1; ++i) ans[i] = tmp[i] % Mod;
    return ans;
  }
  int lim = 1;
  while (lim < (n + m - 1)) lim <<= 1;
  Poly ans(lim);
  A.resize(lim), B.resize(lim);
  getr(lim);
  NTT(A, lim, false), NTT(B, lim, false);
  for (int i = 0; i < lim; ++i) ans[i] = 1ll * A[i] * B[i] % Mod;
  NTT(ans, lim, true);
  ans.resize(n + m - 1);
  return ans;
}
Poly Tmul(Poly A, int n, Poly B, int m) {
  if (1ll * n * m < 64) {
    Poly ans(m - n + 1);
    std::fill(tmp, tmp + m - n + 2, 0);
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n && j <= i; ++j) tmp[j - i] += 1ll * B[i] * A[j] % Mod;
    for (int i = 0; i < m - n + 1; ++i) ans[i] = tmp[i] % Mod;
  }
  int lim = 1;
  while (lim < m) lim <<= 1;
  Poly ans(lim);
  std::reverse(A.begin(), A.begin() + n);
  A.resize(lim), B.resize(lim);
  getr(lim);
  NTT(A, lim, false), NTT(B, lim, false);
  for (int i = 0; i < lim; ++i) ans[i] = 1ll * A[i] * B[i] % Mod;
  NTT(ans, lim, true);
  for (int i = 0; i <= m - n; ++i) ans[i] = ans[i + n - 1];
  ans.resize(m - n + 1);
  return ans;
}
void getg(int x, int xl, int xr, int *f, int m) {
  if (xl == xr) {
    G[x].resize(2);
    G[x][0] = 1;
    if (xl > m)
      G[x][1] = 0;
    else
      G[x][1] = Mod - f[xl];
    return;
  }
  int xm = (xl + xr) >> 1;
  getg(x << 1, xl, xm, f, m), getg(x << 1 | 1, xm + 1, xr, f, m);
  G[x] = mult(G[x << 1], xm - xl + 2, G[x << 1 | 1], xr - xm + 1);
}
void getans(int x, int xl, int xr, int *ans, int m, const Poly &h) {
  if (xl >= m) return;
  if (xl == xr) return void(ans[xl] = h[0]);
  int xm = (xl + xr) >> 1;
  Poly hl = Tmul(G[x << 1 | 1], xr - xm + 1, h, xr - xl + 2);
  getans(x << 1, xl, xm, ans, m, hl);
  Poly hr = Tmul(G[x << 1], xm - xl + 2, h, xr - xl + 2);
  getans(x << 1 | 1, xm + 1, xr, ans, m, hr);
}
void getv(const Poly &A, int n, int *f, int *ans, int m) {
  n = std::max(n, m);
  getg(1, 0, n - 1, f, m);
  Poly now = inv(G[1], n);
  std::reverse(now.begin(), now.begin() + n);
  Poly h = mult(now, n, A, n);
  for (int i = 0; i < n; ++i) h[i] = h[i + n - 1];
  h.resize(n);
  getans(1, 0, n - 1, ans, m, h);
}
void getr(int lim) {
  for (int i = 0; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
}
void init_Poly() {
  for (int l = 1; l < (1 << 19); l <<= 1) {
    gw[l] = 1;
    int gn = pow(g, (Mod - 1) / (l << 1), Mod);
    for (int j = 1; j < l; ++j) {
      gw[l | j] = 1ll * gw[l | (j - 1)] * gn % Mod;
    }
  }
}
}  // namespace Pol

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) ans = 1ll * ans * now % m;
    now = 1ll * now * now % m;
    b >>= 1;
  }
  return ans;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!isNum(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (isNum(ch)) {
    k = (k << 1) + (k << 3) + ch - '0';
    ch = getchar();
  }
  Re = flag * k;
}
template <typename T>
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
