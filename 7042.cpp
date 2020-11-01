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

template <class T>
void read(T &);
template <class T>
void write(const T &);

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

int main() {
  int T;
  read(T);
  while (T--) {
    ll a, b, c, d;
    read(a), read(b), read(c), read(d);
    if (a == b && b == c && c == d) {
      write(1), EL;
      continue;
    }
    ll sum = a + b + c + d;
    if (sum & 1) {
      write(0), EL;
      continue;
    }
    sum >>= 1;
    if (a > b) {
      std::swap(a, b);
    }
    if (b > c) {
      std::swap(b, c);
    }
    if (c > d) {
      std::swap(c, d);
    }
    if (a > b) {
      std::swap(a, b);
    }
    if (b > c) {
      std::swap(b, c);
    }
    if (c > d) {
      std::swap(c, d);
    }
    if (a > b) {
      std::swap(a, b);
    }
    if (b > c) {
      std::swap(b, c);
    }
    if (c > d) {
      std::swap(c, d);
    }
    if (a > b) {
      std::swap(a, b);
    }
    if (b > c) {
      std::swap(b, c);
    }
    if (c > d) {
      std::swap(c, d);
    }
    if (a + d == sum) {
      int cnt = (a == d) + (a == b) + (b == c);
      if (cnt == 0) {
        write(8), EL;
      } else {
        write(4), EL;
      }
    } else {
      write(0), EL;
      continue;
    }
  }
  return 0;
}

template <class T>
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
template <class T>
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
