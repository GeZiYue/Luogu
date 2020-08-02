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

const int N = 1005;
const double dwn = 0.9;

void calc();

double ansx, ansy;
double move = 5000;
int x[N], y[N], m[N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(x[i]), read(y[i]), read(m[i]);
  }
  while (true) {
    double tmpx = ansx, tmpy = ansy;
    calc();
    if (abs(tmpx - ansx) < 1e-4 && abs(tmpy - ansy) < 1e-4) {
      break;
    } else {
      move *= dwn;
    }
  }
  std::cout.precision(3);
  std::cout << std::fixed << ansx << ' ' << ansy << std::endl;
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

void calc() {
  double mx = 0, my = 0;
  for (int i = 1; i <= n; ++i) {
    double tx = x[i] - ansx, ty = y[i] - ansy;
    double tv = sqrt(tx * tx + ty * ty);
    if (abs(tv) < 1e-7) {
      continue;
    }
    mx += (m[i] * tx / tv);
    my += (m[i] * ty / tv);
  }
  double mv = sqrt(mx * mx + my * my);
  if (abs(mv) < 1e-7) {
    return;
  }
  ansx += (move * mx / mv);
  ansy += (move * my / mv);
}
