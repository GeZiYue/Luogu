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

const int N = 50005;

class Point {
public:
  int x, y;
  Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
};
typedef Point Vector;
Vector operator - (const Point &, const Point &);
int cross(const Vector &, const Vector &);
int dis(const Point &, const Point &);
int chk(const Point &, const Point &, const Point &);

Point a[N];
int con[N], top;

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i].x), read(a[i].y);
  }
  sort(a + 1, a + n + 1, [](const Point &i, const Point &j) {
    return (i.x == j.x) ? (i.y < j.y) : (i.x < j.x);
  });
  {
    for (int i = 1; i <= n; ++i) {
      while (top > 1 && chk(a[con[top - 1]], a[con[top]], a[i]) <= 0) {
        --top;
      }
      con[++top] = i;
    }
    int k = top;
    for (int i = n; i >= 1; --i) {
      while (top > k && chk(a[con[top - 1]], a[con[top]], a[i]) <= 0) {
        --top;
      }
      con[++top] = i;
    }
  }
  int ans = 0;
  for (int i = 1, j = 2; i < top; ++i) {
    while (chk(a[con[i]], a[con[i + 1]], a[con[j]]) < chk(a[con[i]], a[con[i + 1]], a[con[j + 1]])) {
      j = j % top + 1;
    }
    ans = max(ans, max(dis(a[con[i]], a[con[j]]), dis(a[con[i + 1]], a[con[j]])));
  }
  write(ans), EL;
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

Vector operator - (const Point &i, const Point &j) {
  return Vector(i.x - j.x, i.y - j.y);
}
int cross(const Vector &i, const Vector &j) {
  return i.x * j.y - i.y * j.x;
}
int dis(const Point &i, const Point &j) {
  return (i.x - j.x) * (i.x - j.x) + (i.y - j.y) * (i.y - j.y);
}
int chk(const Point &i, const Point &j, const Point &k) {
  return cross(j - i, k - i);
}
