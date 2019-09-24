#include <unordered_set>
#include <unordered_map>
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
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 105;
const int Mod = 4147;

void mult(int[N][N], int[N][N]);

int n;
int tmp[N][N];
int a[N][N];
int b[N][N];
int ans[N][N];

int main () {
  int m;
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(b[i][1]);
  }
  for (int i = 1; i <= n; ++i) {
    read(a[1][i]);
  }
  for (int i = 2; i <= n; ++i) {
    a[i][i - 1] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    ans[i][i] = 1;
  }
  m -= n;
  while (m) {
    if (m & 1) {
      mult(ans, a);
    }
    mult(a, a);
    m >>= 1;
  }
  mult(ans, b);
  write(ans[1][1]), EL;
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

inline void mult(int a[N][N], int b[N][N]) {
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      tmp[i][j] = 0;
      for (int k = 1; k <= n; ++k) {
        tmp[i][j] = (tmp[i][j] + a[i][k] * b[k][j]) % Mod;
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      a[i][j] = tmp[i][j];
    }
  }
}
