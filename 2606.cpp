#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
void read(T&);
template<class T>
void write(const T&);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;

const int N = 1000005;

int pow(int, int, int);
int C(int, int);

int fac[N], ifac[N];
int lg2[N];
int f[N];
int n, mod;

int main () {
  read(n), read(mod);
  fac[0] = 1;
  int lim = min(n, mod - 1);
  for (int i = 1; i <= lim; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % mod;
  }
  ifac[lim] = pow(fac[lim], mod - 2, mod);
  for (int i = lim - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % mod;
  }
  for (int i = 2; i <= n; ++i) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  f[1] = f[2] = 1;
  f[3] = 2;
  for (int i = 4, l = 1, r = 1; i <= n; ++i) {
    if (i - (1 << lg2[i]) + 1 <= (1 << (lg2[i] - 1))) {
      ++l;
    } else {
      ++r;
    }
    f[i] = C(i - 1, l) * 1ll * f[l] % mod * f[r] % mod;
  }
  write(f[n]), EL;
  return 0;
}

template<class T>
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
template<class T>
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
int C(int n, int m) {
  if (m == 0) {
    return 1;
  }
  if (n < m) {
    return 0;
  }
  return C(n / mod, m / mod) * 1ll * fac[n] % mod * ifac[m] % mod * ifac[n - m] % mod;
}
