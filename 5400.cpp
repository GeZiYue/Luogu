#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

constexpr int N = 5000000;
constexpr int Mod = 998244353;

int pow(int a, int b, int m);
int C(int n, int m);

int fac[N + 5], ifac[N + 5];
int inv[N + 5], s[N + 5];
int T;
int n, m, l, k;

int main() {
  fac[0] = 1;
  for (int i = 1; i <= N; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[N] = pow(fac[N], Mod - 2, Mod);
  for (int i = N - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  read(T);
  while (T--) {
    read(n), read(m), read(l), read(k);
    int all = n * 1ll * m % Mod * l % Mod;
    int lim = min({n, m, l});
    for (int i = 1; i <= lim; ++i) {
      inv[i] = (all - (n - i) * 1ll * (m - i) % Mod * (l - i) % Mod + Mod) % Mod;
      s[i] = inv[i];
    }
    for (int i = 2; i <= lim; ++i) {
      inv[i] = inv[i - 1] * 1ll * inv[i] % Mod;
    }
    inv[0] = 1;
    for (int i = lim, is = pow(inv[lim], Mod - 2, Mod); i >= 1; --i) {
      inv[i] = inv[i - 1] * 1ll * is % Mod;
      is = is * 1ll * s[i] % Mod;
    }
    int S = 1;
    int ans = 0;
    for (int i = 1; i <= lim; ++i) {
      S = S * 1ll * (n - i + 1) % Mod * (m - i + 1) % Mod * (l - i + 1) % Mod * inv[i] % Mod;
      if (i >= k) {
        int sgn = ((i - k) & 1) ? Mod - 1 : 1;
        ans = (ans + sgn * 1ll * S % Mod * C(i, k) % Mod) % Mod;
      }
    }
    write(ans), EL;
  }
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
int C(int n, int m) { return fac[n] * 1ll * ifac[m] % Mod * ifac[n - m] % Mod; }

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
