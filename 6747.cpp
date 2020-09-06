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

int a[N];
int cnt[100];
int n;
int q;

int main () {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    for (int j = 30; j >= 0; --j) {
      if ((a[i] >> j) & 1) {
        ++cnt[j];
      }
    }
  }
  read(q);
  for (int i = 1; i <= q; ++i) {
    ll m;
    read(m);
    ll now = 0;
    ll k = 0;
    for (int j = 0; j <= 50; ++j) {
      if (n - cnt[j] <= cnt[j]) {
        k |= (1ll << j);
        now += (n - cnt[j]) * (1ll << j);
      } else {
        now += cnt[j] * (1ll << j);
      }
    }
    for (int j = 50; j >= 0 && now < m; --j) {
      if (!(k & (1ll << j))) {
        if ((m - now) / (1ll << j) < (n - cnt[j] * 2)) {
          continue;
        }
        if (now + (n - cnt[j] * 2) * (1ll << j) <= m) {
          k |= (1ll << j);
          now += (n - cnt[j] * 2) * (1ll << j);
        }
      }
    }
    if (now > m) {
      write(-1), EL;
    } else {
      write(k), EL;
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
