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

const int N = 280000;
const int Mod = 998244353, g = 3;
typedef std::vector<int> Poly;

int pow(int a, int b, int m);
int add(int a, int b) { return (a += b) >= Mod ? a -= Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a += Mod : a; }

namespace Pol {
void getr(int lim);
void init_Poly();
void NTT(int *A, int lim, bool flag);
Poly inv(Poly A, int n);
Poly mult(const Poly &A, int n, const Poly &B, int m);
Poly Tmul(const Poly &A, int n, const Poly &B, int m);
void getv(Poly A, int n, int *f, int *ans, int m);
Poly lagrange(int *vx, int *vy, int n);
Poly G[N << 1];
Poly M[N << 1];
ull tmp[N];
int gw[N];
int r[N];
}  // namespace Pol

int x[N], y[N];
int n;

int main() {
  Pol::init_Poly();
  read(n);
  for (int i = 0; i < n; ++i) {
    read(x[i]), read(y[i]);
  }
  Poly ans = Pol::lagrange(x, y, n);
  for (int i = 0; i < n; ++i) write(ans[i]), SP;
  EL;
  return 0;
}

namespace Pol {
void NTT(int *A, int lim, bool flag) {
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
    for (int i = 0; i < lim; ++i) tmp[i] = tmp[i] % Mod * iv;
  }
  for (int i = 0; i < lim; ++i) A[i] = tmp[i] % Mod;
}
Poly mult(const Poly &A, int n, const Poly &B, int m) {
  if (n + m < 500) {
    Poly ans(n + m - 1);
    std::fill(tmp, tmp + n + m, 0);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) tmp[i + j] += 1ll * A[i] * B[j] % Mod;
    for (int i = 0; i < n + m - 1; ++i) ans[i] = tmp[i] % Mod;
    return ans;
  }
  int lim = 1;
  while (lim < (n + m - 1)) lim <<= 1;
  static int tA[N], tB[N];
  std::copy_n(A.begin(), n, tA), std::fill(tA + n, tA + lim, 0);
  std::copy_n(B.begin(), m, tB), std::fill(tB + m, tB + lim, 0);
  getr(lim);
  NTT(tA, lim, false), NTT(tB, lim, false);
  for (int i = 0; i < lim; ++i) tA[i] = 1ll * tA[i] * tB[i] % Mod;
  NTT(tA, lim, true);
  Poly ans(n + m - 1);
  std::copy_n(tA, n + m - 1, ans.begin());
  return ans;
}
Poly Tmul(const Poly &A, int n, const Poly &B, int m) {
  if (n + m < 500) {
    Poly ans(m - n + 1);
    std::fill(tmp, tmp + m - n + 2, 0);
    for (int i = 0; i < m; ++i)
      for (int j = 0; j < n && j <= i; ++j) tmp[j - i] += 1ll * B[i] * A[j] % Mod;
    for (int i = 0; i < m - n + 1; ++i) ans[i] = tmp[i] % Mod;
  }
  int lim = 1;
  while (lim < m) lim <<= 1;
  static int tA[N], tB[N];
  std::reverse_copy(A.begin(), A.begin() + n, tA), std::fill(tA + n, tA + lim, 0);
  std::copy_n(B.begin(), m, tB), std::fill(tB + m, tB + lim, 0);
  getr(lim);
  NTT(tA, lim, false), NTT(tB, lim, false);
  for (int i = 0; i < lim; ++i) tA[i] = 1ll * tA[i] * tB[i] % Mod;
  NTT(tA, lim, true);
  Poly ans(m - n + 1);
  std::copy_n(tA + n - 1, m - n + 1, ans.begin());
  return ans;
}
Poly inv(Poly A, int n) {
  int lim = 1;
  while (lim < (n << 1)) lim <<= 1;
  Poly F(lim), G(lim);
  A.resize(lim);
  G[0] = pow(A[0], Mod - 2, Mod);
  int now = 1;
  static int tA[N], tB[N];
  while (now < n) {
    std::copy_n(A.begin(), now << 1, F.begin());
    int lim = now << 2;
    getr(lim);
    std::copy_n(G.begin(), lim, tA);
    std::copy_n(F.begin(), lim, tB);
    NTT(tA, lim, false), NTT(tB, lim, false);
    for (int i = 0; i < lim; ++i) tA[i] = 1ll * sub(2, 1ll * tA[i] * tB[i] % Mod) * tA[i] % Mod;
    NTT(tA, lim, true);
    std::copy_n(tA, now << 1, G.begin());
    now <<= 1;
  }
  G.resize(n);
  return G;
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
  Poly hl = Tmul(G[x << 1 | 1], xr - xm + 1, h, xr - xl + 1);
  getans(x << 1, xl, xm, ans, m, hl);
  Poly hr = Tmul(G[x << 1], xm - xl + 2, h, xr - xl + 1);
  getans(x << 1 | 1, xm + 1, xr, ans, m, hr);
}
void getv(Poly A, int n, int *f, int *ans, int m) {
  n = std::max(n, m);
  A.resize(n);
  getg(1, 0, n - 1, f, m);
  Poly now = inv(G[1], n);
  std::reverse(now.begin(), now.begin() + n);
  Poly h = mult(now, n, A, n);
  for (int i = 0; i <= n; ++i) h[i] = h[i + n - 1];
  h.resize(n + 1);
  getans(1, 0, n - 1, ans, m, h);
}
void getm(int x, int xl, int xr, int *vx) {
  if (xl == xr) {
    M[x].resize(2);
    M[x][1] = 1, M[x][0] = Mod - vx[xl];
    return;
  }
  int xm = (xl + xr) >> 1;
  getm(x << 1, xl, xm, vx), getm(x << 1 | 1, xm + 1, xr, vx);
  M[x] = mult(M[x << 1], xm - xl + 2, M[x << 1 | 1], xr - xm + 1);
}
Poly getp(int x, int xl, int xr, int *vx, int *v) {
  if (xl == xr) {
    Poly F(1);
    F[0] = v[xl];
    return F;
  }
  int xm = (xl + xr) >> 1;
  Poly Fl = getp(x << 1, xl, xm, vx, v), Fr = getp(x << 1 | 1, xm + 1, xr, vx, v);
  Fl = mult(Fl, xm - xl + 1, M[x << 1 | 1], xr - xm + 1);
  Fr = mult(Fr, xr - xm, M[x << 1], xm - xl + 2);
  Poly F(xr - xl + 1);
  for (int i = 0; i <= xr - xl; ++i) {
    F[i] = (Fl[i] + Fr[i]) % Mod;
  }
  return F;
}
Poly lagrange(int *vx, int *vy, int n) {
  getm(1, 0, n - 1, vx);
  Poly M0 = M[1];
  for (int i = 0; i < n; ++i) {
    M0[i] = 1ll * M0[i + 1] * (i + 1) % Mod;
  }
  M0[n] = 0;
  static int v[N], f[N];
  for (int i = 0; i < n; ++i) {
    f[i] = vx[i];
  }
  getv(M0, n, f, v, n);
  for (int i = 0; i < n; ++i) {
    v[i] = 1ll * vy[i] * pow(v[i], Mod - 2, Mod) % Mod;
  }
  Poly F = getp(1, 0, n - 1, vx, v);
  return F;
}
void getr(int lim) {
  for (int i = 0; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
}
void init_Poly() {
  for (int l = 1; l < (1 << 18); l <<= 1) {
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
