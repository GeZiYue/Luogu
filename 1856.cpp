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
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

class Line {
public:
  int x1, x2, y;
  int num;
  bool operator < (const Line &i) const {
    if (y == i.y) {
      return num > i.num;
    }
    return y < i.y;
  }
}a[N], b[N];

void update(int, int, int, int, int, int);

pii x[N], y[N];
int cov[N << 2];
int sum[N << 2];
bool lc[N << 2], rc[N << 2];

int main () {
  int n;
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(x[(i << 1) - 1].first), read(a[i << 1].y), read(x[i << 1].first), read(a[(i << 1) - 1].y);
    x[(i << 1) - 1].second = (i << 1) - 1;
    x[i << 1].second = i << 1;
    a[(i << 1) - 1].num = -1;
    a[i << 1].num = 1;
    b[(i << 1) - 1].y = x[(i << 1) - 1].first;
    b[i << 1].y = x[i << 1].first;
    y[(i << 1) - 1] = pii(a[i << 1].y, (i << 1) - 1);
    y[i << 1] = pii(a[(i << 1) - 1].y, i << 1);
    b[(i << 1) - 1].num = 1;
    b[i << 1].num = -1;
  }
  sort(x + 1, x + (n << 1) + 1);
  x[0].first = -1;
  ll ans = 0;
  int now = 0;
  for (int i = 1; i <= (n << 1); ++i) {
    if (x[i].first ^ x[i - 1].first) {
      ++now;
    }
    if (x[i].second & 1) {
      a[x[i].second].x1 = now;
      a[x[i].second + 1].x1 = now;
    } else {
      a[x[i].second - 1].x2 = now - 1;
      a[x[i].second].x2 = now - 1;
    }
  }
  sort(a + 1, a + (n << 1) + 1);
  for (int i = 1; i <= (n << 1); ++i) {
    update(1, 1, now, a[i].x1, a[i].x2, a[i].num);
    ans += sum[1] * (a[i + 1].y - a[i].y) * 2;
  }
  sort(y + 1, y + (n << 1) + 1);
  y[0].first = -1;
  now = 0;
  for (int i = 1; i <= (n << 1); ++i) {
    if (y[i].first ^ y[i - 1].first) {
      ++now;
    }
    if (y[i].second & 1) {
      b[y[i].second].x1 = now;
      b[y[i].second + 1].x1 = now;
    } else {
      b[y[i].second - 1].x2 = now - 1;
      b[y[i].second].x2 = now - 1;
    }
  }
  sort(b + 1, b + (n << 1) + 1);
  for (int i = 1; i <= (n << 1); ++i) {
    update(1, 1, now, b[i].x1, b[i].x2, b[i].num);
    ans += sum[1] * (b[i + 1].y - b[i].y) * 2;
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

void pushup(int x, int xl, int xr) {
  if (cov[x]) {
    sum[x] = 1;
    lc[x] = rc[x] = true;
  } else {
    sum[x] = sum[ls(x)] + sum[rs(x)] - (rc[ls(x)] && lc[rs(x)]);
    lc[x] = lc[ls(x)], rc[x] = rc[rs(x)];
  }
}
void update(int x, int xl, int xr, int ul, int ur, int num) {
  if (xl > ur || xr < ul) {
    return;
  }
  if (xl >= ul && xr <= ur) {
    cov[x] += num;
    if (cov[x] > 0) {
      sum[x] = 1;
      lc[x] = rc[x] = true;
    } else {
      if (xl == xr) {
        sum[x] = 0;
        lc[x] = rc[x] = false;
      } else {
        pushup(x, xl, xr);
      }
    }
    return;
  }
  int xm = (xl + xr) >> 1;
  update(ls(x), xl, xm, ul, ur, num);
  update(rs(x), xm + 1, xr, ul, ur, num);
  pushup(x, xl, xr);
}
