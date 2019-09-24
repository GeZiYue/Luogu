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
const int N = 20005;
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
}a[N];

void update(int, int, int, int, int, int);

pii x[N];
int maxn[N << 2];
int tag[N << 2];

int main () {
  int t;
  read(t);
  while (t--) {
    memset(maxn, 0, sizeof(maxn));
    memset(tag, 0, sizeof(tag));
    int n, w, h;
    read(n), read(w), read(h);
    ++w, ++h;
    for (int i = 1; i <= n; ++i) {
      int xi, yi, li;
      read(xi), read(yi), read(li);
      x[(i << 1) - 1] = pii(xi - w + 1, (i << 1) - 1);
      x[i << 1] = pii(xi - 1, i << 1);
      a[(i << 1) - 1].y = yi - h + 1;
      a[i << 1].y = yi - 1;
      a[(i << 1) - 1].num = li;
      a[i << 1].num = -li;
    }
    sort(x + 1, x + (n << 1) + 1);
    x[0].first = -iinf;
    int now = 0;
    for (int i = 1; i <= (n << 1); ++i) {
      if (x[i].first ^ x[i - 1].first) {
        ++now;
      }
      if (x[i].second & 1) {
        a[x[i].second].x1 = now;
        a[x[i].second + 1].x1 = now;
      } else {
        a[x[i].second - 1].x2 = now;
        a[x[i].second].x2 = now;
      }
    }
    sort(a + 1, a + (n << 1) + 1);
    int ans = 0;
    for (int i = 1; i <= (n << 1); ++i) {
      update(1, 1, now, a[i].x1, a[i].x2, a[i].num);
      ans = max(ans, maxn[1]);
    }
    write(ans), EL;
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

void pushup(int x) {
  maxn[x] = max(maxn[ls(x)], maxn[rs(x)]);
}
void pushdown(int x) {
  if (tag[x]) {
    maxn[ls(x)] += tag[x], maxn[rs(x)] += tag[x];
    tag[ls(x)] += tag[x], tag[rs(x)] += tag[x];
    tag[x] = 0;
  }
}
void update(int x, int xl, int xr, int ul, int ur, int num) {
  if (xl > ur || xr < ul) {
    return;
  }
  if (xl >= ul && xr <= ur) {
    maxn[x] += num;
    tag[x] += num;
    return;
  }
  pushdown(x);
  int xm = (xl + xr) >> 1;
  update(ls(x), xl, xm, ul, ur, num);
  update(rs(x), xm + 1, xr, ul, ur, num);
  pushup(x);
}
