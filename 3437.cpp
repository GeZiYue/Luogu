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
#define lc(x) (x << 1)
#define rc(x) (x << 1 | 1)
const int N = 1005;

class Node {
public:
  int lc, rc;
  int tag;
  int val;
};

int query(int, int, int, int, int, int, int);
void update(int, int, int, int, int, int, int, int);

Node tre[N * 1000 * 8];
int tot;
int tag[N << 2], maxn[N << 2];
int n, m, q;

int main () {
  read(n), read(m), read(q);
  for (int i = 1; i <= q; ++i) {
    int d, s, h, x, y;
    read(d), read(s), read(h), read(x), read(y);
    int opl = x + 1, opr = x + d, opx = y + 1, opy = y + s;
    update(1, 1, n, opl, opr, opx, opy, query(1, 1, n, opl, opr, opx, opy) + h);
  }
  write(query(1, 1, n, 1, n, 1, m)), EL;
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

void update(int &x, int xl, int xr, int ux, int uy, int num) {
  if (!x) {
    x = ++tot;
  }
  tre[x].val = max(tre[x].val, num);
  if (xl >= ux && xr <= uy) {
    tre[x].tag = max(tre[x].tag, num);
    return;
  }
  int xm = (xl + xr) >> 1;
  if (ux <= xm) {
    update(tre[x].lc, xl, xm, ux, uy, num);
  }
  if (uy > xm) {
    update(tre[x].rc, xm + 1, xr, ux, uy, num);
  }
}
int query(int x, int xl, int xr, int qx, int qy) {
  if (!x) {
    return 0;
  }
  if (xl >= qx && xr <= qy) {
    return tre[x].val;
  }
  int ans = tre[x].tag;
  int xm = (xl + xr) >> 1;
  if (qx <= xm) {
    ans = max(ans, query(tre[x].lc, xl, xm, qx, qy));
  }
  if (qy > xm) {
    ans = max(ans, query(tre[x].rc, xm + 1, xr, qx, qy));
  }
  return ans;
}
void update(int x, int xl, int xr, int ul, int ur, int ux, int uy, int num) {
  update(maxn[x], 1, m, ux, uy, num);
  if (xl >= ul && xr <= ur) {
    update(tag[x], 1, m, ux, uy, num);
    return;
  }
  int xm = (xl + xr) >> 1;
  if (ul <= xm) {
    update(lc(x), xl, xm, ul, ur, ux, uy, num);
  }
  if (ur > xm) {
    update(rc(x), xm + 1, xr, ul, ur, ux, uy, num);
  }
}
int query(int x, int xl, int xr, int ql, int qr, int qx, int qy) {
  if (xl >= ql && xr <= qr) {
    return query(maxn[x], 1, m, qx, qy);
  }
  int ans = query(tag[x], 1, m, qx, qy);
  int xm = (xl + xr) >> 1;
  if (ql <= xm) {
    ans = max(ans, query(lc(x), xl, xm, ql, qr, qx, qy));
  }
  if (qr > xm) {
    ans = max(ans, query(rc(x), xm + 1, xr, ql, qr, qx, qy));
  }
  return ans;
}
