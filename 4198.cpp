#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

const int N = 100005;

int query(int x, int xl, int xr, double maxx);
void update(int x, int xl, int xr, int ux, double num);

int sum[N << 2];
double maxn[N << 2];
int n, q;

int main() {
  read(n), read(q);
  for (int i = 1; i <= q; ++i) {
    int x, y;
    read(x), read(y);
    update(1, 1, n, x, y * 1.0 / x);
    write(sum[1]), EL;
  }
  return 0;
}

template <class T>
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
template <class T>
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

int query(int x, int xl, int xr, double maxx) {
  if (maxn[x] <= maxx) {
    return 0;
  }
  if (xl == xr) {
    return 1;
  }
  int xm = (xl + xr) >> 1;
  if (maxn[x << 1] <= maxx) {
    return query(x << 1 | 1, xm + 1, xr, maxx);
  }
  return query(x << 1, xl, xm, maxx) + sum[x] - sum[x << 1];
}
void update(int x, int xl, int xr, int ux, double num) {
  if (xl == xr) {
    maxn[x] = num;
    sum[x] = 1;
    return;
  }
  int xm = (xl + xr) >> 1;
  if (ux <= xm) {
    update(x << 1, xl, xm, ux, num);
  } else {
    update(x << 1 | 1, xm + 1, xr, ux, num);
  }
  maxn[x] = max(maxn[x << 1], maxn[x << 1 | 1]);
  sum[x] = sum[x << 1] + query(x << 1 | 1, xm + 1, xr, maxn[x << 1]);
}
