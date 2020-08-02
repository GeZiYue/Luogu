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
#include <ctime>
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

const int N = (1 << 20);
const int Mod = 1000000009;

int count[N];
int a[21][N], b[21][N], c[21][N];

int main () {
  int n;
  read(n);
  for (int i = 1; i < (1 << n); ++i) {
    count[i] = count[i >> 1] + (i & 1);
  }
  for (int i = 0; i < (1 << n); ++i) {
    read(a[count[i]][i]);
  }
  for (int i = 0; i < (1 << n); ++i) {
    read(b[count[i]][i]);
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < (1 << n); ++k) {
        if (k & (1 << j)) {
          a[i][k] = (a[i][k] + a[i][k ^ (1 << j)]) % Mod;
          b[i][k] = (b[i][k] + b[i][k ^ (1 << j)]) % Mod;
        }
      }
    }
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= i; ++j) {
      for (int k = 0; k < (1 << n); ++k) {
        c[i][k] = (c[i][k] + a[j][k] * 1ll * b[i - j][k] % Mod) % Mod;
      }
    }
  }
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < (1 << n); ++k) {
        if (k & (1 << j)) {
          c[i][k] = (c[i][k] + Mod - c[i][k ^ (1 << j)]) % Mod;
        }
      }
    }
  }
  for (int i = 0; i < (1 << n); ++i) {
    write(c[count[i]][i]), SP;
  }
  EL;
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
