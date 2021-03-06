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

const int N = 105;
const double eps = 1e-6;

double a[N][N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n + 1; ++j) {
      scanf("%lf", &a[i][j]);
    }
  }
  for (int i = 1; i <= n; ++i) {
    int md = i;
    for (int j = i + 1; j <= n; ++j) {
      if (abs(a[j][i]) > abs(a[md][i])) {
        md = j;
      }
    }
    if (abs(a[md][i]) < eps) {
      puts("No Solution");
      return 0;
    }
    if (i != md) {
      std::swap(a[i], a[md]);
    }
    for (int j = n + 1; j >= i; --j) {
      a[i][j] /= a[i][i];
    }
    for (int j = i + 1; j <= n; ++j) {
      for (int k = n + 1; k >= i; --k) {
        a[j][k] -= a[j][i] * a[i][k];
      }
    }
  }
  for (int i = n - 1; i >= 1; --i) {
    for (int j = i + 1; j <= n; ++j) {
      a[i][n + 1] -= a[i][j] * a[j][n + 1];
    }
  }
  for (int i = 1; i <= n; ++i) {
    printf("%.2lf\n", a[i][n + 1]);
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
