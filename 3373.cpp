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
const int N = 100005;
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)

void build(int, int, int);
void updatea(int, int, int, int, int, int);
void updatem(int, int, int, int, int, int);
int query(int, int, int, int, int);

int p;
int sum[N << 2], taga[N << 2], tagm[N << 2];
int a[N];

int main () {
  int n, m;
  read(n), read(m), read(p);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  build(1, 1, n);
  for (int i = 1; i <= m; ++i) {
    int type, l, r;
    read(type), read(l), read(r);
    if (type == 3) {
      write(query(1, 1, n, l, r)), EL;
    } else {
      int num;
      read(num);
      if (type == 1) {
        updatem(1, 1, n, l, r, num);
      } else {
        updatea(1, 1, n, l, r, num);
      }
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

inline void pushup(int x) {
  sum[x] = (sum[ls(x)] + sum[rs(x)]) % p;
}
inline void pushdown(int x, int xl, int xr) {
  if (tagm[x] != 1) {
    sum[ls(x)] = sum[ls(x)] * 1ll * tagm[x] % p;
    sum[rs(x)] = sum[rs(x)] * 1ll * tagm[x] % p;
    taga[ls(x)] = taga[ls(x)] * 1ll * tagm[x] % p;
    taga[rs(x)] = taga[rs(x)] * 1ll * tagm[x] % p;
    tagm[ls(x)] = tagm[ls(x)] * 1ll * tagm[x] % p;
    tagm[rs(x)] = tagm[rs(x)] * 1ll * tagm[x] % p;
    tagm[x] = 1;
  }
  if (taga[x]) {
    int xm = (xl + xr) >> 1;
    sum[ls(x)] = (sum[ls(x)] + (xm - xl + 1) * 1ll * taga[x] % p) % p;
    sum[rs(x)] = (sum[rs(x)] + (xr - xm) * 1ll * taga[x] % p) % p;
    taga[ls(x)] = (taga[ls(x)] + taga[x]) % p;
    taga[rs(x)] = (taga[rs(x)] + taga[x]) % p;
    taga[x] = 0;
  }
}
void build(int x, int xl, int xr) {
  if (xl == xr) {
    sum[x] = a[xl] % p;
    return;
  }
  taga[x] = 0;
  tagm[x] = 1;
  int xm = (xl + xr) >> 1;
  build(ls(x), xl, xm), build(rs(x), xm + 1, xr);
  pushup(x);
}
void updatea(int x, int xl, int xr, int ul, int ur, int num) {
  if (xl > ur || xr < ul) {
    return;
  }
  if (xl >= ul && xr <= ur) {
    sum[x] = (sum[x] + (xr - xl + 1) * 1ll * num % p) % p;
    taga[x] = (taga[x] + num) % p;
    return;
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  updatea(ls(x), xl, xm, ul, ur, num);
  updatea(rs(x), xm + 1, xr, ul, ur, num);
  pushup(x);
}
void updatem(int x, int xl, int xr, int ul, int ur, int num) {
  if (xl > ur || xr < ul) {
    return;
  }
  if (xl >= ul && xr <= ur) {
    sum[x] = sum[x] * 1ll * num % p;
    taga[x] = taga[x] * 1ll * num % p;
    tagm[x] = tagm[x] * 1ll * num % p;
    return;
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  updatem(ls(x), xl, xm, ul, ur, num);
  updatem(rs(x), xm + 1, xr, ul, ur, num);
  pushup(x);
}
int query(int x, int xl, int xr, int ql, int qr) {
  if (xl > qr || xr < ql) {
    return 0;
  }
  if (xl >= ql && xr <= qr) {
    return sum[x];
  }
  pushdown(x, xl, xr);
  int xm = (xl + xr) >> 1;
  return (
    query(ls(x), xl, xm, ql, qr) +
    query(rs(x), xm + 1, xr, ql, qr)
  ) % p;
}
