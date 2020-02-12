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

const int N = 200005;

double sqr(double);
void add(int);
void del(int);
bool check(int);

int a[N];
int len;
ll sum;
double ave, var;
int n;
ll m;

int main () {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  sort(a + 1, a + n + 1);
  int l = 1, r = n, ans = 0;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
      ans = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  write(n - ans), EL;
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

inline double sqr(double x) {
  return x * x;
}
inline void add(int x) {
  if (len == 0) {
    len = 1;
    sum = a[x];
    ave = a[x];
    var = 0;
    return;
  }
  double av2 = (sum + a[x]) * 1.0 / (len + 1);
  var += sqr(a[x] - av2);
  var += 2.0 * ave * sum;
  var -= 2.0 * av2 * sum;
  var -= sqr(ave) * len;
  var += sqr(av2) * len;
  ++len;
  sum += a[x];
  ave = av2;
}
inline void del(int x) {
  if (len == 1) {
    len = 0;
    sum = 0;
    ave = 0;
    var = 0;
    return;
  }
  var -= sqr(a[x] - ave);
  --len;
  sum -= a[x];
  double av2 = sum * 1.0 / len;
  var += 2.0 * ave * sum;
  var -= 2.0 * av2 * sum;
  var -= sqr(ave) * len;
  var += sqr(av2) * len;
  ave = av2;
}
bool check(int x) {
  int l = 1, r = 0;
  len = 0;
  for (; r < x;) {
    add(++r);
  }
  if (var <= m) {
    return true;
  }
  for (; r < n;) {
    del(l++);
    add(++r);
    if (var <= m) {
      return true;
    }
  }
  return false;
}
