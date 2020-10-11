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

const int N = 21;
const int M = 1 << 20;

double p[M];
int siz[M];
int n, S;

int main() {
  read(n);
  S = 1 << n;
  for (int i = 0; i < S; ++i) {
    std::cin >> p[i];
  }
  for (int l = 1; l < S; l <<= 1) {
    for (int i = 0; i < S; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        p[i | j | l] += p[i | j];
      }
    }
  }
  for (int i = 1; i < S; ++i) {
    siz[i] = siz[i >> 1] + (i & 1);
  }
  double ans = 0;
  for (int i = 1; i < S; ++i) {
    ans += ((siz[i] & 1) ? 1 : -1) / (1 - p[(S - 1) ^ i]);
  }
  if (!std::isfinite(ans)) {
    std::cout << "INF" << std::endl;
  } else {
    std::cout.precision(10);
    std::cout << ans << std::endl;
  }
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
