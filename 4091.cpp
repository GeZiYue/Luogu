#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 100005;
const int Mod = 998244353, iv3 = 332748118;

int pow(int a, int b, int m);
int C(int n, int m);
void work(int n);

bool isp[N];
int pri[N], pw[N], id;
int fac[N], ifac[N], inv[N];
int f[N], d0[N], dn[N];
int n;

int main() {
  read(n);
  work(n);
  fac[0] = 1;
  for (int i = 1; i <= n + 1; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n + 1] = pow(fac[n + 1], Mod - 2, Mod);
  for (int i = n; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  for (int i = 1; i <= n + 1; ++i) {
    inv[i] = fac[i - 1] * 1ll * ifac[i] % Mod;
  }
  f[0] = 1, f[1] = n + 1;
  for (int i = 2; i <= n; ++i) {
    f[i] = (pw[i] - 1) * 1ll * inv[i - 1] % Mod;
  }
  const int i2 = Mod - 2, i3 = Mod - 3;
  int t1 = pow(i2, n + 1, Mod) * 1ll * pow(i3, Mod - 2, Mod) % Mod,
      t2 = i2 * 1ll * pow(3, Mod - 2, Mod) % Mod;
  d0[0] = pow(i3, Mod - 2, Mod);
  dn[0] = t1;
  for (int i = 1; i <= n; ++i) {
    d0[i] = d0[i - 1] * 1ll * t2 % Mod;
    dn[i] = (t1 * 1ll * C(n + 1, i) + t2 * 1ll * dn[i - 1] % Mod) % Mod;
  }
  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    if (i & 1) {
      ans = (ans - f[i] * 1ll * (dn[i] - d0[i] + Mod) % Mod + Mod) % Mod;
    } else {
      ans = (ans + f[i] * 1ll * (dn[i] - d0[i] + Mod) % Mod) % Mod;
    }
  }
  write(ans), EL;
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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
void work(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
      pw[i] = pow(i, n + 1, Mod);
    }
    for (int j = 1; j <= id && pri[j] * i <= n; ++j) {
      isp[pri[j] * i] = true;
      pw[pri[j] * i] = pw[pri[j]] * 1ll * pw[i] % Mod;
      if (i % pri[j] == 0) {
        break;
      }
    }
  }
}
