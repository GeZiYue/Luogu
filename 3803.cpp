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

const int N = 2100000;
const int Mod = 998244353, g = 3;
typedef std::vector<int> Poly;

int pow(int a, int b, int m);

namespace Pol {
int add(int a, int b) { return (a += b) >= Mod ? a -= Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a += Mod : a; }
void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
void init_Poly(int n = N);
void DIT(Poly &A, int lim, int len);
void DIF(Poly &A, int lim);
Poly mult(Poly A, int n, Poly B, int m);
int gw[N], igw[N];
}  // namespace Pol

int n, m;

int main() {
  Pol::init_Poly();
  read(n), read(m);
  ++n, ++m;
  Poly F(n), G(m);
  for (int i = 0; i < n; ++i) read(F[i]);
  for (int i = 0; i < m; ++i) read(G[i]);
  Poly ans = Pol::mult(F, n, G, m);
  for (int i = 0; i < n + m - 1; ++i) write(ans[i]), SP;
  EL;
  return 0;
}

namespace Pol {
void DIT(Poly &A, int lim, int len) {
  for (int l = 1; l < lim; l <<= 1) {
    auto k = A.begin();
    for (; k < A.begin() + lim; k += (l << 1)) {
      auto x = k;
      for (int *ig = igw + l; x < k + l; ++x, ++ig) {
        int o = 1ll * x[l] * *ig % Mod;
        x[l] = sub(*x, o), inc(*x, o);
      }
    }
  }
  int iv = pow(lim, Mod - 2, Mod);
  for (int i = 0; i < len; ++i) A[i] = 1ll * A[i] * iv % Mod;
}
void DIF(Poly &A, int lim) {
  for (int l = lim / 2; l >= 1; l >>= 1) {
    auto k = A.begin();
    for (; k < A.begin() + lim; k += (l << 1)) {
      auto x = k;
      for (int *g = gw + l; x < k + l; ++x, ++g) {
        int o = x[l];
        x[l] = 1ll * (*x + Mod - o) * *g % Mod;
        inc(*x, o);
      }
    }
  }
}
Poly mult(Poly A, int n, Poly B, int m) {
  int lim = 1;
  while (lim < (n + m - 1)) lim <<= 1;
  A.resize(lim), B.resize(lim);
  DIF(A, lim), DIF(B, lim);
  for (int i = 0; i < lim; ++i) A[i] = 1ll * A[i] * B[i] % Mod;
  DIT(A, lim, lim);
  Poly ans(n + m - 1);
  std::copy_n(A.begin(), n + m - 1, ans.begin());
  return ans;
}
void init_Poly(int n) {
  int t = std::min(int(log(n) / log(2)), 21);
  gw[1 << t] = pow(31, 1 << (21 - t));
  for (int i = 21; i >= 0; --i) {
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
