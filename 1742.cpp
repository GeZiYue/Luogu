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

const int N = 100005;

class Point {
public:
  double x, y;
  Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
};
typedef Point Vector;
class Circle {
public:
  Point O;
  double r;
  Circle(Point OO = Point(), double rr = 0) : O(OO), r(rr) {}
};

double sqr(double);
bool chk(double, double);
double dis(const Point &, const Point &);
Circle getc(const Point &, const Point &, const Point &);

Point a[N];

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i].x >> a[i].y;
  }
  std::random_shuffle(a + 1, a + n + 1);
  Circle ans;
  for (int i = 1; i <= n; ++i) {
    if (chk(ans.r, dis(ans.O, a[i]))) {
      continue;
    }
    ans = Circle(
      Point(
        (a[1].x + a[i].x) / 2,
        (a[1].y + a[i].y) / 2
      ),
      dis(a[1], a[i]) / 2
    );
    for (int j = 2; j < i; ++j) {
      if (chk(ans.r, dis(ans.O, a[j]))) {
        continue;
      }
      ans = Circle(
        Point(
          (a[i].x + a[j].x) / 2,
          (a[i].y + a[j].y) / 2
        ),
        dis(a[i], a[j]) / 2
      );
      for (int k = 1; k < j; ++k) {
        if (chk(ans.r, dis(ans.O, a[k]))) {
          continue;
        }
        ans = getc(a[i], a[j], a[k]);
      }
    }
  }
  std::cout.precision(10);
  std::cout << std::fixed << ans.r << std::endl << ans.O.x << ' ' << ans.O.y << std::endl;
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

double sqr(double x) {
  return x * x;
}
bool chk(double a, double b) {
  if (a >= b || fabs(b - a) <= 1e-9) {
    return true;
  } else {
    return false;
  }
}
double dis(const Point &a, const Point &b) {
  return sqrt(sqr(b.x - a.x) + sqr(b.y - a.y));
}
Circle getc(const Point &a, const Point &b, const Point &c) {
  double a1 = b.x - a.x, a2 = c.x - a.x, b1 = b.y - a.y, b2 = c.y - a.y;
  double c1 = (sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y)) / 2;
  double c2 = (sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y)) / 2;
  Circle ans;
  ans.O = Point(
    (b2 * c1 - b1 * c2) / (b2 * a1 - b1 * a2),
    (a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2)
  );
  ans.r = dis(ans.O, a);
  return ans;
}
