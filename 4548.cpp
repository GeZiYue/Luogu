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
const int Mod = 10000;

int a[N];
int nxt[N];
int power[N];

int main () {
  int n, t;
  read(n), read(t);
  power[0] = 1;
  for (int i = 1; i <= 100000; ++i) {
    power[i] = power[i - 1] * n % Mod;
  }
  for (int i = 1; i <= t; ++i) {
    int m;
    read(m);
    for (int j = 1; j <= m; ++j) {
      read(a[j]);
    }
    for (int j = 2, k = 0; j <= m; ++j) {
      while (k && a[k + 1] != a[j]) {
        k = nxt[k];
      }
      k += (a[k + 1] == a[j]);
      nxt[j] = k;
    }
    int tmp = m;
    int ans = 0;
    while (tmp) {
      ans = (ans + power[tmp]) % Mod;
      tmp = nxt[tmp];
    }
    std::cout.width(4);
    std::cout.fill('0');
    std::cout << ans << std::endl;
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
