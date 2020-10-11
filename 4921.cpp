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

const int N = 5000000;
const int Mod = 998244353;

int pow(int a, int b, int m);
int C(int n, int k);

int fac[N + 1], ifac[N + 1];
int d[N];
int T, n, k;

int main() {
  d[0] = 1, d[1] = 0;
  for (int i = 2; i <= N; ++i) {
    d[i] = (4ll * i * (i - 1) % Mod * d[i - 1] +
            8ll * (i - 1) * (i - 1) % Mod * i % Mod * d[i - 2] % Mod) %
           Mod;
  }
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
    int n;
    read(n);
    for (int k = 0; k <= n; ++k) {
      int tmp = C(n, k);
      tmp = tmp * 1ll * tmp % Mod;
      write(tmp * 1ll * fac[k] % Mod * pow(2, k, Mod) % Mod * d[n - k] % Mod),
          EL;
    }
  }
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
int C(int n, int k) { return fac[n] * 1ll * ifac[k] % Mod * ifac[n - k] % Mod; }
