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

const int N = 505;
const double eps = 1e-8;

class Point;
typedef Point Vector;
class Point {
public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
};
Vector operator + (Point i, Point j) {
  return Vector(i.x + j.x, i.y + j.y);
}
Vector operator - (Point i, Point j) {
  return Vector(i.x - j.x, i.y - j.y);
}
Vector operator * (Vector i, double j) {
  return Vector(i.x * j, i.y * j);
}
double cross(Vector i, Vector j) {
  return i.x * j.y - i.y * j.x;
}
class Line {
public:
  Point a;
  Vector v;
  double k;
  Line(Point x = Point(), Point y = Point()) : a(x), v(y - x) {}
};
bool operator < (Line i, Line j) {
  if (fabs(i.k - j.k) > eps) {
    return i.k < j.k;
  } else {
    return cross(i.v, j.a - i.a) > 0;
  }
}
Point insec(Line i, Line j) {
  Vector u = i.a - j.a;
  double t = cross(j.v, u) / cross(i.v, j.v);
  return i.a + i.v * t;
}

Line L[N];
int id;
Point t[N];
int q[N], qh, qt;

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    int m;
    read(m);
    Point fir, las;
    scanf("%lf %lf", &fir.x, &fir.y);
    las = fir;
    for (int j = 2; j <= m; ++j) {
      Point now;
      scanf("%lf %lf", &now.x, &now.y);
      L[++id] = Line(las, now);
      las = now;
    }
    L[++id] = Line(las, fir);
  }
  for (int i = 1; i <= id; ++i) {
    L[i].k = atan2(L[i].v.y, L[i].v.x);
  }
  sort(L + 1, L + id + 1);
  {
    int cnt = 0;
    for (int i = 1; i < id; ++i) {
      if (fabs(L[i].k - L[i + 1].k) < eps) {
        continue;
      }
      L[++cnt] = L[i];
    }
    L[++cnt] = L[id];
    id = cnt;
  }
  qh = 1, qt = 0;
  for (int i = 1; i <= id; ++i) {
    while (qt > qh && cross(L[i].v, t[qt] - L[i].a) < 0) {
      --qt;
    }
    while (qt > qh && cross(L[i].v, t[qh + 1] - L[i].a) < 0) {
      ++qh;
    }
    q[++qt] = i;
    if (qt > qh) {
      t[qt] = insec(L[q[qt - 1]], L[q[qt]]);
    }
  }
  while (qt > qh && cross(L[q[qh]].v, t[qt] - L[q[qh]].a) < 0) {
    --qt;
  }
  t[qt + 1] = insec(L[q[qt]], L[q[qh]]);
  ++qt;
  double ans = 0;
  for (int i = qh + 1; i < qt; ++i) {
    ans += cross(t[i], t[i + 1]);
  }
  ans += cross(t[qt], t[qh + 1]);
  ans /= 2;
  printf("%.3lf\n", ans);
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
