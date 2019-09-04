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
const int N = 10005;

class Point {
public:
  double x, y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
  inline bool operator < (const Point &i) const {
    if (x == i.x) {
      return y < i.y;
    } else {
      return x < i.x;
    }
  }
};

double getk(const int&, const int&);
double far(const int&, const int&);

Point a[N];
int que[N], siz;

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    std::cin >> a[i].x >> a[i].y;
  }
  sort(a + 1, a + n + 1);
  double ans = 0;
  siz = 0;
  for (int i = 1; i <= n; ++i) {
    while (siz >= 2 && getk(que[siz - 1], que[siz]) > getk(que[siz - 1], i)) {
      --siz;
    }
    que[++siz] = i;
  }
  for (int i = 2; i <= siz; ++i) {
    ans += far(que[i - 1], que[i]);
  }
  siz = 0;
  for (int i = n; i >= 1; --i) {
    while (siz >= 2 && getk(que[siz - 1], que[siz]) > getk(que[siz - 1], i)) {
      --siz;
    }
    que[++siz] = i;
  }
  for (int i = 2; i <= siz; ++i) {
    ans += far(que[i - 1], que[i]);
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

inline double getk(const int &i, const int &j) {
  return a[j].x == a[i].x ? iinf : (a[j].y - a[i].y) / (a[j].x - a[i].x);
}
inline double far(const int &i, const int &j) {
  return sqrt((a[j].x - a[i].x) * (a[j].x - a[i].x) + (a[j].y - a[i].y) * (a[j].y - a[i].y));
}
