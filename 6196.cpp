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

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 5000005;

int a[N];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  a[0] = a[n + 1] = 1;
  ll ans = 0;
  int las = 0;
  for (int i = 1; i <= n + 1; ++i) {
    if (a[i] == 1) {
      if (i == las + 1) {
        las = i;
        ++ans;
        continue;
      }
      for (int j = las + 1; j < i - 1; ++j) {
        ans += a[j] * a[j + 1];
      }
      int now = iinf;
      for (int j = las + 1; j < i; ++j) {
        now = min(now, a[j]);
      }
      ans += now;
      ++ans;
      las = i;
    }
  }
  write(ans - 1), EL;
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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
