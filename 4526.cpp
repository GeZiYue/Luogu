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

double f(double);
double simpson(double, double);
double solve(double, double, double, double);

double a;

int main () {
  std::cin >> a;
  if (a < 0) {
    puts("orz");
  } else {
    std::cout.precision(5);
    std::cout << std::fixed << solve(1e-7, 20, 1e-7, simpson(1e-7, 20)) << std::endl;
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

double f(double x) {
  return pow(x, a / x - x);
}
double simpson(double l, double r) {
  return (r - l) * (f(l) + f(r) + f((l + r) / 2) * 4) / 6;
}
double solve(double l, double r, double eps, double A) {
  double m = (l + r) / 2;
  double L = simpson(l, m), R = simpson(m, r);
  if (abs(L + R - A) <= 15 * eps) {
    return L + R + (L + R - A) / 15;
  } else {
    return solve(l, m, eps / 2, L) + solve(m, r, eps / 2, R);
  }
}
