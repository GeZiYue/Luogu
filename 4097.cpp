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
const int M = 40005;
typedef std::pair<double, double> line;

bool check(int l1, int l2, int x);
void add(int x, int xl, int xr, int al, int ar, int num);
int query(int x, int xl, int xr, int qx);

line L[N];
int maxi[M << 2];
int n;

int main () {
  read(n);
  int lasans = 0;
  int id = 0;
  for (int i = 1; i <= n; ++i) {
    int op;
    read(op);
    if (op) {
      int x0, x1, y0, y1;
      read(x0), read(y0), read(x1), read(y1);
      x0 = (x0 + lasans - 1) % 39989 + 1;
      x1 = (x1 + lasans - 1) % 39989 + 1;
      y0 = (y0 + lasans - 1) % 1000000000 + 1;
      y1 = (y1 + lasans - 1) % 1000000000 + 1;
      ++id;
      if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
      }
      if (x0 == x1) {
        L[id].first = 0;
        L[id].second = max(y0, y1);
      } else {
        L[id].first = (y1 - y0) * 1.0 / (x1 - x0);
        L[id].second = y0 - L[id].first * x0;
      }
      add(1, 1, 39989, x0, x1, id);
    } else {
      int x;
      read(x);
      x = (x + lasans - 1) % 39989 + 1;
      write(lasans = query(1, 1, 39989, x)), EL;
    }
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

bool check(int l1, int l2, int x) {
  if (!l1) {
    return false;
  }
  if (!l2) {
    return true;
  }
  return x * L[l1].first + L[l1].second > x * L[l2].first + L[l2].second;
}
void add(int x, int xl, int xr, int al, int ar, int num) {
  int xm = (xl + xr) >> 1;
  if (xl >= al && xr <= ar) {
    bool sl = check(num, maxi[x], xl), sr = check(num, maxi[x], xr);
    if (sl && sr) {
      maxi[x] = num;
      return;
    }
    if (!sl && !sr) {
      return;
    }
    bool sm = check(num, maxi[x], xm);
    if (sl) {
      if (sm) {
        add(x << 1 | 1, xm + 1, xr, al, ar, maxi[x]);
        maxi[x] = num;
      } else {
        add(x << 1, xl, xm, al, ar, num);
      }
    } else {
      if (sm) {
        add(x << 1, xl, xm, al, ar, maxi[x]);
        maxi[x] = num;
      } else {
        add(x << 1 | 1, xm + 1, xr, al, ar, num);
      }
    }
    return;
  }
  if (al <= xm) {
    add(x << 1, xl, xm, al, ar, num);
  }
  if (ar > xm) {
    add(x << 1 | 1, xm + 1, xr, al, ar, num);
  }
}
int query(int x, int xl, int xr, int qx) {
  int ans = maxi[x];
  if (xl == xr) {
    return maxi[x];
  }
  int xm = (xl + xr) >> 1;
  if (qx <= xm) {
    int al = query(x << 1, xl, xm, qx);
    if (check(al, ans, qx)) {
      ans = al;
    }
  } else {
    int ar = query(x << 1 | 1, xm + 1, xr, qx);
    if (check(ar, ans, qx)) {
      ans = ar;
    }
  }
  return ans;
}
