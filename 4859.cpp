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

const int N = 2005;
const int Mod = 1000000009;

int pow(int, int, int);

int fac[N], ifac[N];
int dp[N][N];
int a[N], b[N];
int r[N];

int main () {
  int n, k;
  read(n), read(k);
  if ((n + k) & 1) {
    puts("0");
    return 0;
  } else {
    k = (n + k) >> 1;
  }
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 1; i <= n; ++i) {
    read(b[i]);
  }
  sort(a + 1, a + n + 1);
  sort(b + 1, b + n + 1);
  b[n + 1] = iinf;
  for (int i = 1; i <= n; ++i) {
    r[i] = r[i - 1];
    while (a[i] > b[r[i] + 1]) {
      ++r[i];
    }
  }
  dp[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    dp[i][0] = dp[i - 1][0];
    for (int j = 1; j <= i; ++j) {
      dp[i][j] = (dp[i - 1][j] + (r[i] - j + 1) * 1ll * dp[i - 1][j - 1] % Mod) % Mod;
    }
  }
  int ans = 0;
  for (int i = k; i <= n; ++i) {
    ans = (ans + (((i - k) & 1) ? (Mod - 1) : 1) * 1ll * fac[i] % Mod * ifac[k] % Mod * ifac[i - k] % Mod * dp[n][i] % Mod * fac[n - i] % Mod) % Mod;
  }
  write(ans), EL;
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
