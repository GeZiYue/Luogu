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

constexpr int N = 405;
constexpr int Mod = 1000000007;

int pow(int a, int b, int m);
bool Gauss(int n);

int a[N][N << 1];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      read(a[i][j]);
    }
    a[i][n + i] = 1;
  }
  if (Gauss(n)) {
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        write(a[i][j + n]), SP;
      }
      EL;
    }
  } else {
    puts("No Solution");
  }
  return 0;
}

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
bool Gauss(int n) {
  for (int i = 1; i <= n; ++i) {
    int now = 0;
    for (int j = i; j <= n; ++j) {
      if (a[j][i]) {
        now = j;
        break;
      }
    }
    if (!now) {
      return false;
    }
    std::swap(a[i], a[now]);
    int iv = pow(a[i][i], Mod - 2, Mod);
    for (int j = i; j <= (n << 1); ++j) {
      a[i][j] = a[i][j] * 1ll * iv % Mod;
    }
    for (int j = 1; j <= n; ++j) {
      if (i ^ j) {
        for (int k = (n << 1); k >= i; --k) {
          a[j][k] = (a[j][k] - a[j][i] * 1ll * a[i][k] % Mod + Mod) % Mod;
        }
      }
    }
  }
  return true;
}
