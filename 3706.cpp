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

const int N = 305;
const int Mod = 1000000007;

int hash(int, int, int);
void Guess(int);

int bin[N];
int has[N][N];
double f[N][N];
double bd[N];
char ch[N];
int n, m;

int main () {
  read(n), read(m);
  bin[0] = 1, bd[0] = 1.0;
  for (int i = 1; i <= m; ++i) {
    bin[i] = (bin[i - 1] << 1) % Mod;
    bd[i] = bd[i - 1] * 2.0;
  }
  for (int i = 1; i <= n; ++i) {
    scanf("%s", ch + 1);
    for (int j = 1; j <= m; ++j) {
      has[i][j] = ((has[i][j - 1] << 1) % Mod + (ch[j] == 'H')) % Mod;
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      for (int k = 1; k <= m; ++k) {
        if (hash(i, 1, k) == hash(j, m - k + 1, m)) {
          f[i][j] += bd[k];
        }
      }
    }
    f[i][n + 1] = -1;
  }
  for (int i = 1; i <= n; ++i) {
    f[n + 1][i] = 1;
  }
  f[n + 1][n + 2] = 1;
  Guess(n + 1);
  std::cout.precision(8);
  for (int i = 1; i <= n; ++i) {
    std::cout << std::fixed << f[i][n + 2] << std::endl;
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

int hash(int i, int l, int r) {
  return (has[i][r] - has[i][l - 1] * 1ll * bin[r - l + 1] % Mod + Mod) % Mod;
}
void Guess(int n) {
  for (int i = 1; i <= n; ++i) {
    int md = i;
    for (int j = i + 1; j <= n; ++j) {
      if (abs(f[j][i]) > abs(f[md][i])) {
        md = j;
      }
    }
    if (i != md) {
      std::swap(f[i], f[md]);
    }
    for (int j = n + 1; j >= i; --j) {
      f[i][j] /= f[i][i];
    }
    for (int j = i + 1; j <= n; ++j) {
      for (int k = n + 1; k >= i; --k) {
        f[j][k] -= f[j][i] * f[i][k];
      }
    }
  }
  for (int i = n - 1; i >= 1; --i) {
    for (int j = i + 1; j <= n; ++j) {
      f[i][n + 1] -= f[i][j] * f[j][n + 1];
    }
  }
}
