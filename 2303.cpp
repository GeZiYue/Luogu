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

int phi(unsigned int);

int main () {
  unsigned int n;
  read(n);
  ll ans = 0;
  for (unsigned int i = 1; i * 1ll * i <= n; ++i) {
    if (n % i == 0) {
      ans += phi(n / i) * 1ll * i;
      if (i * i != n) {
        ans += phi(i) * 1ll * (n / i);
      }
    }
  }
  write(ans), EL;
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

int phi(unsigned int x) {
  unsigned int ans = x;
  for (int i = 2; i * i <= x; ++i) {
    if (x % i == 0) {
      ans = ans / i * (i - 1);
      while (x % i == 0) {
        x /= i;
      }
    }
  }
  if (x != 1) {
    ans = ans / x * (x - 1);
  }
  return ans;
}
