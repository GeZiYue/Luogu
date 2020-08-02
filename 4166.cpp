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

const int N = 3005;

class Point;
typedef Point Vector;
class Point {
public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  bool operator <(const Point &) const;
  Vector operator -(const Point &) const;
};
double cross(const Vector &, const Vector &);
double dis(const Point &, const Point &);
double check(int, int, int);

Point p[N];
int cov[N], siz;
int n;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    scanf("%lf %lf", &p[i].x, &p[i].y);
  }
  sort(p + 1, p + n + 1);
  {
    for (int i = 1; i <= n; ++i) {
      while (siz > 1 && check(cov[siz - 1], cov[siz], i) <= 0) {
        --siz;
      }
      cov[++siz] = i;
    }
    int now = siz;
    for (int i = n - 1; i >= 1; --i) {
      while (siz > now && check(cov[siz - 1], cov[siz], i) <= 0) {
        --siz;
      }
      cov[++siz] = i;
    }
  }
  if (siz < 4) {
    write(0), EL;
    return 0;
  }
  if (siz == 4) {
    double ans = abs(check(cov[1], cov[2], cov[3]));
    double now = 1e13;
    for (int i = 1; i <= n; ++i) {
      if (i != cov[1] && i != cov[2] && i != cov[3]) {
        if (abs(check(i, cov[1], cov[2])) > 0) {
          now = min(now, abs(check(i, cov[1], cov[2])));
        }
        if (abs(check(i, cov[2], cov[3])) > 0) {
          now = min(now, abs(check(i, cov[2], cov[3])));
        }
        if (abs(check(i, cov[3], cov[1])) > 0) {
          now = min(now, abs(check(i, cov[3], cov[1])));
        }
      }
    }
    ans -= now;
    printf("%.3lf\n", ans / 2);
  } else {
    double ans = 0;
    for (int i = 1, j = 2; i < siz; ++i) {
      while (check(cov[i], cov[i + 1], cov[j]) < check(cov[i], cov[i + 1], cov[j + 1])) {
        j = j % (siz - 1) + 1;
      }
      int k;
      if (dis(p[cov[i]], p[cov[j]]) > dis(p[cov[i + 1]], p[cov[j]])) {
        k = i;
      } else {
        k = i % (siz - 1) + 1;
      }
      double a1 = 0, a2 = 0;
      for (int l = j; l != k; l = l % (siz - 1) + 1) {
        a1 = max(a1, abs(check(cov[l], cov[j], cov[k])));
      }
      for (int l = k; l != j; l = l % (siz - 1) + 1) {
        a2 = max(a2, abs(check(cov[l], cov[j], cov[k])));
      }
      ans = max(ans, a1 + a2);
    }
    printf("%.3lf\n", ans / 2);
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

bool Point::operator <(const Point &i) const {
  if (x == i.x) {
    return y < i.y;
  }
  return x < i.x;
}
Vector Point::operator -(const Point &i) const {
  return Vector(i.x - x, i.y - y);
}
double cross(const Vector &i, const Vector &j) {
  return i.x * j.y - i.y * j.x;
}
double dis(const Point &i, const Point &j) {
  return sqrt((j.x - i.x) * (j.x - i.x) + (j.y - i.y) * (j.y - i.y));
}
double check(int i, int j, int k) {
  return cross(p[j] - p[i], p[k] - p[i]);
}
