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
const int Mod = 998244353, g = 3, sgn[] = {1, Mod - 1};
typedef std::vector<int> Poly;

void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
int pow(int a, int b, int m);
void getr(int lim);
void NTT(Poly &a, int lim, bool opt);
int C(int n, int m);
Poly solve(int len, int l, int r);
Poly mult(int l, int r);

int fac[N], ifac[N];
int iv[N];
int gw[N];
int r[N];
int a[N];
std::vector<Poly> S;
std::vector<int> Ln;
int n, k;

int main() {
  for (int l = 1; l < (1 << 19); l <<= 1) {
    gw[l] = 1;
    int gn = pow(g, (Mod - 1) / (l << 1), Mod);
    for (int i = 1; i < l; ++i) {
      gw[l | i] = 1ll * gw[l | (i - 1)] * gn % Mod;
    }
  }
  read(n), read(k);
  iv[1] = 1;
  for (int i = 2; i <= n; ++i) iv[i] = 1ll * (Mod - Mod / i) * iv[Mod % i] % Mod;
  for (int i = 2; i <= n; ++i) inc(iv[i], iv[i - 1]);
  for (int i = 1; i <= n; ++i) iv[i] = 1ll * iv[i] * n % Mod;
  for (int i = 1; i <= n; ++i) read(a[i]);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) fac[i] = 1ll * fac[i - 1] * i % Mod;
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % Mod;
  std::sort(a + 1, a + n + 1);
  int len = 1;
  for (int i = 2; i <= n; ++i) {
    if (a[i] == a[i - 1] + 1) {
      ++len;
    } else {
      if (len >= k) Ln.push_back(len);
      len = 1;
    }
  }
  if (len >= k) Ln.push_back(len);
  for (int l : Ln) {
    Poly ans = solve(l, 0, l / (k + 1));
    ans.resize(l + 1);
    Poly tmp = solve(l - k, 0, (l - k) / (k + 1));
    tmp.resize(l - k + 1);
    for (int i = 0; i <= l - k; ++i) dec(ans[i + k], tmp[i]);
    S.push_back(ans);
  }
  int siz = S.size();
  Poly ans = mult(0, siz - 1);
  ans.resize(n + 1);
  int res = 0;
  for (int i = 1; i <= n; ++i) dec(res, 1ll * ans[i] * iv[i] % Mod);
  write(res), EL;
  return 0;
}

Poly solve(int len, int l, int r) {
  if (l == r) {
    Poly ans(1);
    ans[0] = C(len - l * k, l);
    return ans;
  }
  int mid = (l + r) >> 1;
  int lim = 1;
  while (lim <= (r - l) * (k + 1)) lim <<= 1;
  Poly L = solve(len, l, mid), R = solve(len, mid + 1, r);
  getr(lim);
  L.resize(lim), R.resize(lim);
  int lL = mid - l + 1;
  Poly F(lim);
  for (int i = 0; i <= lL; ++i) inc(F[i + lL * k], 1ll * C(lL, i) * sgn[(lL - i) & 1] % Mod);
  NTT(F, lim, false), NTT(R, lim, false);
  for (int i = 0; i < lim; ++i) R[i] = 1ll * R[i] * F[i] % Mod;
  NTT(R, lim, true);
  for (int i = 0; i < lim; ++i) inc(R[i], L[i]);
  return R;
}
Poly mult(int l, int r) {
  if (l == r) {
    return S[l];
  }
  int mid = (l + r) >> 1;
  Poly L = mult(l, mid), R = mult(mid + 1, r);
  int len = 0;
  for (int i = l; i <= r; ++i) len += Ln[i];
  int lim = 1;
  while (lim <= len) lim <<= 1;
  getr(lim);
  L.resize(lim), R.resize(lim);
  NTT(L, lim, false), NTT(R, lim, false);
  for (int i = 0; i < lim; ++i) L[i] = 1ll * L[i] * R[i] % Mod;
  NTT(L, lim, true);
  return L;
}

void NTT(Poly &a, int lim, bool opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) std::swap(a[i], a[r[i]]);
  }
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        int x = a[i | j], y = 1ll * a[i | j | l] * gw[l | j] % Mod;
        a[i | j] = (x + y) % Mod;
        a[i | j | l] = (x - y + Mod) % Mod;
      }
    }
  }
  if (opt) {
    std::reverse(a.begin() + 1, a.begin() + lim);
    int iv = pow(lim, Mod - 2, Mod);
    for (int i = 0; i < lim; ++i) {
      a[i] = 1ll * a[i] * iv % Mod;
    }
  }
}
void getr(int lim) {
  for (int i = 0; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
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
int C(int n, int m) { return 1ll * fac[n] * ifac[m] % Mod * ifac[n - m] % Mod; }

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
