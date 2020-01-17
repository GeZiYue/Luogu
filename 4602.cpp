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
const int N = 100000;

class Item {
public:
  int d, p, l;
  bool operator<(const Item &i) const {
    return d < i.d;
  }
};
class Node {
public:
  int lc, rc;
  ll val, vas;
};

void insert(int &, int, int, int, int);
ll query(int, int, int, ll);
int find(ll, ll);

Item a[N + 5];
Node tre[N * 20];
int rot[N + 5];
int tot;
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i].d), read(a[i].p), read(a[i].l);
  }
  sort(a + 1, a + n + 1);
  a[0].d = -1;
  for (int i = n; i >= 1; --i) {
    insert(rot[i] = rot[i + 1], 1, N, a[i].p, a[i].l);
  }
  rot[0] = rot[1];
  for (int i = 1; i <= m; ++i) {
    ll p, l;
    read(p), read(l);
    write(find(p, l)), EL;
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

void insert(int &x, int xl, int xr, int p, int l) {
  tre[++tot] = tre[x];
  x = tot;
  tre[x].val += l;
  tre[x].vas += l * 1ll * p;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  if (p <= xm) {
    insert(tre[x].lc, xl, xm, p, l);
  } else {
    insert(tre[x].rc, xm + 1, xr, p, l);
  }
}
ll query(int x, int xl, int xr, ll lim) {
  if (xl == xr) {
    return lim * xl;
  }
  int xm = (xl + xr) >> 1;
  if (lim <= tre[tre[x].lc].val) {
    return query(tre[x].lc, xl, xm, lim);
  } else {
    return tre[tre[x].lc].vas + query(tre[x].rc, xm + 1, xr, lim - tre[tre[x].lc].val);
  }
}
int find(ll qp, ll ql) {
  int l = 0, r = n, ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (ql <= tre[rot[mid]].val && query(rot[mid], 1, N, ql) <= qp) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return a[ans].d;
}
