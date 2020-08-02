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
typedef std::set<pii>::iterator iter;

ll det(int x1, int y1, int x2, int y2);
double dis(iter it1, iter it2);
bool check(int x, int y);
bool del(iter it);
void insert(int x, int y);

std::set<pii> S;
double ans[N];
double now;
int x[N], y[N];
int op[N], num[N];
bool isd[N];
int n, m;

int main () {
  int x0, y0;
  read(n), read(x0), read(y0);
  now = (double)n;
  insert(0, 0), insert(n, 0), insert(x0, y0);
  read(m);
  for (int i = 1; i <= m; ++i) {
    read(x[i]), read(y[i]);
  }
  int q;
  read(q);
  for (int i = 1; i <= q; ++i) {
    read(op[i]);
    if (op[i] == 1) {
      read(num[i]);
      isd[num[i]] = true;
    }
  }
  for (int i = 1; i <= m; ++i) {
    if (!isd[i]) {
      insert(x[i], y[i]);
    }
  }
  for (int i = q; i >= 1; --i) {
    if (op[i] == 1) {
      insert(x[num[i]], y[num[i]]);
    } else {
      ans[i] = now;
    }
  }
  for (int i = 1; i <= q; ++i) {
    if (op[i] == 2) {
      printf("%.2lf\n", ans[i]);
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

ll det(int x1, int y1, int x2, int y2) {
  return x1 * 1ll * y2 - x2 * 1ll * y1;
}
double dis(iter it1, iter it2) {
  return sqrtl((it2->first - it1->first) * 1.0 * (it2->first - it1->first) + (it2->second - it1->second) * 1.0 * (it2->second - it1->second));
}
bool check(int x, int y) {
  iter it = S.lower_bound(pii(x, y));
  if (it == S.end()) {
    return false;
  }
  if (it->first == x) {
    return y < it->second;
  }
  if (it == S.begin()) {
    return false;
  }
  iter jt = it;
  --jt;
  return det(it->first - jt->first, it->second - jt->second, x - jt->first, y - jt->second) <= 0;
}
bool del(iter it) {
  if (it == S.begin()) {
    return false;
  }
  iter jt = it, kt = it;
  --jt, ++kt;
  if (kt == S.end()) {
    return false;
  }
  if (det(it->first - jt->first, it->second - jt->second, kt->first - jt->first, kt->second - jt->second) >= 0) {
    now -= dis(it, jt) + dis(it, kt);
    now += dis(jt, kt);
    S.erase(it);
    return true;
  } else {
    return false;
  }
}
void insert(int x, int y) {
  if (check(x, y)) {
    return;
  }
  iter it = S.insert(pii(x, y)).first;
  if (S.size() >= 3) {
    iter jt = it, kt = it;
    --jt, ++kt;
    now -= dis(jt, kt);
    now += dis(it, jt) + dis(it, kt);
  }
  iter jt = it;
  if (it != S.begin()) {
    --jt;
    while (del(jt++)) {
      --jt;
    }
  }
  if (++jt != S.end()) {
    while (del(jt--)) {
      ++jt;
    }
  }
}
