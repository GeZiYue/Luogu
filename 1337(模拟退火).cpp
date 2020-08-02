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
const double dwn = 0.996;

double dis(double, double, double, double);
double calc_energy(double, double);
void get_ans();

double ansx, ansy, anse;
int x[N], y[N], m[N];
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(x[i]), read(y[i]), read(m[i]);
    ansx += x[i], ansy += y[i];
  }
  ansx /= n, ansy /= n;
  anse = calc_energy(ansx, ansy);
  get_ans();
  get_ans();
  get_ans();
  get_ans();
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

double dis(double x1, double y1, double x2, double y2) {
  return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}
double calc_energy(double x1, double y1) {
  double ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += dis(x[i], y[i], x1, y1) * m[i];
  }
  return ans;
}
void get_ans() {
  double temp = 4000;
  while (temp > 1e-15) {
    double x1 = ansx + (2 * rand() - RAND_MAX) * temp;
    double y1 = ansy + (2 * rand() - RAND_MAX) * temp;
    double e1 = calc_energy(x1, y1);
    if (e1 < anse) {
      ansx = x1, ansy = y1, anse = e1;
    } else {
      if (exp((anse - e1) / temp) * RAND_MAX > rand()) {
        ansx = x1, ansy = y1;
      }
    }
    temp *= dwn;
  }
}
