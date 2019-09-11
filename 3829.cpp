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
const int N = 40005;
const long double PI = acos(-1);

class Vector;
class Point {
  friend Vector;
public:
  long double x, y;
  Point(long double x = 0, long double y = 0) : x(x), y(y) {}
  Point operator +(const Vector &) const;
  Vector operator -(const Point &) const;
};
class Vector {
  friend Point;
public:
  long double x, y;
  Vector(long double x = 0, long double y = 0) : x(x), y(y) {}
  Vector operator -() const;
  Vector inv_rotate(const long double &) const;
  long double mod() const;
};

bool check(const Vector &, const Vector &);

Point pt[N];
int que[N], tot;

int main () {
  int n;
  long double a, b, r;
  read(n);
  std::cin >> b >> a >> r;
  Vector v1(a / 2 - r, b / 2 - r);
  Vector v2(a / 2 - r, r - b / 2);
  Vector v3 = -v1;
  Vector v4 = -v2;
  int cnt = 0;
  long double ans = 2 * PI * r;
  for (int i = 1; i <= n; ++i) {
    Point p;
    long double theta;
    std::cin >> p.x >> p.y >> theta;
    pt[++cnt] = p + v1.inv_rotate(theta);
    pt[++cnt] = p + v2.inv_rotate(theta);
    pt[++cnt] = p + v3.inv_rotate(theta);
    pt[++cnt] = p + v4.inv_rotate(theta);
  }
  sort(pt + 1, pt + cnt + 1, [](const Point &i, const Point &j) {
    if (i.x == j.x) {
      return i.y < j.y;
    } else {
      return i.x < j.x;
    }
  });
  tot = 0;
  for (int i = 1; i <= cnt; ++i) {
    while (tot >= 2 && check(pt[que[tot]] - pt[que[tot - 1]], pt[i] - pt[que[tot - 1]])) {
      --tot;
    }
    que[++tot] = i;
  }
  for (int i = 1; i < tot; ++i) {
    ans += (pt[que[i + 1]] - pt[que[i]]).mod();
  }
  tot = 0;
  for (int i = cnt; i >= 1; --i) {
    while (tot >= 2 && check(pt[que[tot]] - pt[que[tot - 1]], pt[i] - pt[que[tot - 1]])) {
      --tot;
    }
    que[++tot] = i;
  }
  for (int i = 1; i < tot; ++i) {
    ans += (pt[que[i + 1]] - pt[que[i]]).mod();
  }
  std::cout.precision(2);
  std::cout << std::fixed << ans << std::endl;
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

inline Point Point::operator +(const Vector &v) const {
  return Point(x + v.x, y + v.y);
}
inline Vector Point::operator -(const Point &p) const {
  return Vector(p.x - x, p.y - y);
}

inline Vector Vector::operator -() const {
  return Vector(-x, -y);
}
inline Vector Vector::inv_rotate(const long double &theta) const {
  return Vector(x * cos(theta) - y * sin(theta), x * sin(theta) + y * cos(theta));
}
inline long double Vector::mod() const {
  return sqrt(x * x + y * y);
}

bool check(const Vector &v1, const Vector &v2) {
  return v1.x * v2.y - v1.y * v2.x <= 0;
}
