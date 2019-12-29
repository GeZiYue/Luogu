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
#define lowbit(x) (x & -x)
const int N = 50005;
const int M = 100000000;

class Node {
public:
  int lc, rc;
  int val;
};

void build(int, int);
void change(int, int);
int queryrank(int, int, int);
int queryk(int, int, int);

Node tre[40000005];
int tot;
int rot[N];
int add[N];
int sub[N];
int a[N];
int n, m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    build(i, a[i]);
  }
  for (int i = 1; i <= m; ++i) {
    int opt;
    read(opt);
    if (opt == 3) {
      int x, num;
      read(x), read(num);
      change(x, num);
    } else {
      int l, r, k;
      read(l), read(r), read(k);
      switch (opt) {
      case 1:
        write(queryrank(l, r, k - 1) + 1), EL;
        break;
      case 2:
        write(queryk(l, r, k)), EL;
        break;
      case 4:
        write(queryk(l, r, queryrank(l, r, k - 1))), EL;
        break;
      case 5:
        write(queryk(l, r, queryrank(l, r, k) + 1)), EL;
        break;
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

void insert(int &x, int xl, int xr, int num, int c) {
  if (!x) {
    x = ++tot;
  }
  tre[x].val += c;
  if (xl == xr) {
    return;
  }
  int xm = (xl + xr) >> 1;
  if (num <= xm) {
    insert(tre[x].lc, xl, xm, num, c);
  } else {
    insert(tre[x].rc, xm + 1, xr, num, c);
  }
}
int getrank(int x, int xl, int xr, int num) {
  if (!x) {
    return 0;
  }
  if (xl == xr) {
    return tre[x].val;
  }
  int xm = (xl + xr) >> 1;
  if (num <= xm) {
    return getrank(tre[x].lc, xl, xm, num);
  } else {
    return getrank(tre[x].rc, xm + 1, xr, num) + tre[tre[x].lc].val;
  }
}
int getk(int xl, int xr, int k) {
  if (xl == xr) {
    return xl;
  }
  int xm = (xl + xr) >> 1;
  int cnt = 0;
  for (int i = 1; i <= add[0]; ++i) {
    cnt += tre[tre[add[i]].lc].val;
  }
  for (int i = 1; i <= sub[0]; ++i) {
    cnt -= tre[tre[sub[i]].lc].val;
  }
  if (cnt >= k) {
    for (int i = 1; i <= add[0]; ++i) {
      add[i] = tre[add[i]].lc;
    }
    for (int i = 1; i <= sub[0]; ++i) {
      sub[i] = tre[sub[i]].lc;
    }
    return getk(xl, xm, k);
  } else {
    for (int i = 1; i <= add[0]; ++i) {
      add[i] = tre[add[i]].rc;
    }
    for (int i = 1; i <= sub[0]; ++i) {
      sub[i] = tre[sub[i]].rc;
    }
    return getk(xm + 1, xr, k - cnt);
  }
}
void build(int x, int num) {
  int i = x;
  while (i <= n) {
    insert(rot[i], 0, M, num, 1);
    i += lowbit(i);
  }
}
void change(int x, int num) {
  int i = x;
  while (i <= n) {
    insert(rot[i], 0, M, a[x], -1);
    i += lowbit(i);
  }
  i = x;
  while (i <= n) {
    insert(rot[i], 0, M, num, 1);
    i += lowbit(i);
  }
  a[x] = num;
}
int queryrank(int l, int r, int num) {
  int ans = 0;
  int i = r;
  while (i) {
    ans += getrank(rot[i], 0, M, num);
    i -= lowbit(i);
  }
  i = l - 1;
  while (i) {
    ans -= getrank(rot[i], 0, M, num);
    i -= lowbit(i);
  }
  return ans;
}
int queryk(int l, int r, int k) {
  if (k < 1) {
    return -iinf;
  }
  if (k > (r - l + 1)) {
    return iinf;
  }
  int i = r;
  add[0] = 0;
  while (i) {
    add[++add[0]] = rot[i];
    i -= lowbit(i);
  }
  i = l - 1;
  sub[0] = 0;
  while (i) {
    sub[++sub[0]] = rot[i];
    i -= lowbit(i);
  }
  return getk(0, M, k);
}
