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

namespace Pol {
int add(int a, int b) { return (a += b) >= Mod ? a -= Mod : a; }
int sub(int a, int b) { return (a -= b) < 0 ? a += Mod : a; }
void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }
void init_Poly();
void DIT(Poly &A, int lim, int len);
void DIF(Poly &A, int lim);
Poly inv(Poly A, int n);
int gw[N], igw[N];
}  // namespace Pol

int n;

int main() {
  Pol::init_Poly();
  read(n);
  Poly A(n);
  for (int i = 0; i < n; ++i) read(A[i]);
  Poly Ans = Pol::inv(A, n);
  for (int i = 0; i < n; ++i) write(Ans[i]), SP;
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
Poly inv(Poly A, int n) {
  int lim = 1;
  while (lim < (n << 1)) lim <<= 1;
  Poly F(lim), G(lim);
  A.resize(lim);
  G[0] = pow(A[0], Mod - 2, Mod);
  int now = 1;
  while (now < n) {
    int lim = now << 2;
    std::copy_n(A.begin(), now << 1, F.begin());
    DIF(G, lim), DIF(F, lim);
    for (int i = 0; i < lim; ++i) G[i] = 1ll * sub(2, 1ll * G[i] * F[i] % Mod) * G[i] % Mod;
    DIT(G, lim, now << 1);
    std::fill(G.begin() + (now << 1), G.begin() + lim, 0);
    now <<= 1;
  }
  G.resize(n);
  return G;
}
void init_Poly() {
  for (int l = 1; l < (1 << 18); l <<= 1) {
    gw[l] = 1, igw[l] = 1;
    int gn = pow(g, (Mod - 1) / (l << 1), Mod), ign = pow(gn, Mod - 2, Mod);
    for (int j = 1; j < l; ++j) {
      gw[l | j] = 1ll * gw[l | (j - 1)] * gn % Mod;
      igw[l | j] = 1ll * igw[l | (j - 1)] * ign % Mod;
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
