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

const int N = 1505;
const int Mod = 1000000007;

int add(int a, int b) { a += b; if (a >= Mod) { a -= Mod; } return a; }
int sub(int a, int b) { a -= b; if (a < 0) { a += Mod; } return a; }
int pow(int a, int b, int m);
void Gauss(int n);

int p[N];
int f[N][N];
int T, n, l, m, k;

int main () {
  read(T);
  while (T--) {
    read(n), read(l), read(m), read(k);
    if (m == 0 && k == 1) {
      puts("-1");
      continue;
    }
    if (k == 0) {
      puts("-1");
      continue;
    }
    if (m == 0) {
      int ans = 0;
      while (l > 0) {
        if (l < n) {
          ++l;
        }
        l -= k;
        ++ans;
      }
      write(ans), EL;
      continue;
    }
    int k1 = pow(m + 1, Mod - 2, Mod), k2 = (Mod + 1 - k1) % Mod;
    memset(p, 0, sizeof(p));
    for (int i = 0, m1 = 1, m2 = pow(k2, k, Mod), ik2 = pow(k2, Mod - 2, Mod), fc1 = 1, fc2 = 1;
        i <= min(n, k);
        ++i, m1 = m1 * 1ll * k1 % Mod, m2 = m2 * 1ll * ik2 % Mod) {
      p[i] = fc1 * 1ll * fc2 % Mod * m1 % Mod * m2 % Mod;
      fc1 = fc1 * 1ll * pow(i + 1, Mod - 2, Mod) % Mod;
      fc2 = fc2 * 1ll * (k - i) % Mod;
    }
    memset(f, 0, sizeof(f));
    for (int i = 1; i < n; ++i) {
      f[i][i] = f[i][n + 1] = 1;
      for (int j = 0; j < i; ++j) {
        f[i][i - j] = sub(f[i][i - j], k2 * 1ll * p[j] % Mod);
      }
      for (int j = 0; j <= i; ++j) {
        f[i][i - j + 1] = sub(f[i][i - j + 1], k1 * 1ll * p[j] % Mod);
      }
    }
    f[n][n] = f[n][n + 1] = 1;
    for (int i = 0; i < n; ++i) {
      f[n][n - i] = sub(f[n][n - i], p[i]);
    }
    Gauss(n);
    write(f[l][n + 1]), EL;
  }
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
void Gauss(int n) {
  for (int i = 1; i <= n; ++i) {
    int tmp = pow(f[i][i], Mod - 2, Mod);
    f[i][i] = 1, f[i][n + 1] = f[i][n + 1] * 1ll * tmp % Mod;
    if (i != n) {
      f[i][i + 1] = f[i][i + 1] * 1ll * tmp % Mod;
    }
    for (int j = i + 1; j <= n; ++j) {
      f[j][n + 1] = sub(f[j][n + 1], f[j][i] * 1ll * f[i][n + 1] % Mod);
      f[j][i + 1] = sub(f[j][i + 1], f[j][i] * 1ll * f[i][i + 1] % Mod);
      f[j][i] = 0;
    }
  }
  for (int i = n - 1; i >= 1; --i) {
    f[i][n + 1] = sub(f[i][n + 1], f[i][i + 1] * 1ll * f[i + 1][n + 1] % Mod);
  }
}
