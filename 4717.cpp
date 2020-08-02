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

const int N = 140000;
const int Mod = 998244353;
const int mi = 998244352;

void init(int);
void FWT_OR(int *, int, int);
void FWT_AND(int *, int, int);
void FWT_XOR(int *, int, int);
void mult(int);

int a[N], b[N];
int tmpa[N], tmpb[N];
int n;

int main () {
  read(n);
  n = 1 << n;
  for (int i = 0; i < n; ++i) {
    read(a[i]);
  }
  for (int i = 0; i < n; ++i) {
    read(b[i]);
  }
  init(n);
  FWT_OR(tmpa, n, 1), FWT_OR(tmpb, n, 1);
  mult(n);
  FWT_OR(tmpa, n, mi);
  for (int i = 0; i < n; ++i) {
    write(tmpa[i]), SP;
  }
  EL;
  init(n);
  FWT_AND(tmpa, n, 1), FWT_AND(tmpb, n, 1);
  mult(n);
  FWT_AND(tmpa, n, mi);
  for (int i = 0; i < n; ++i) {
    write(tmpa[i]), SP;
  }
  EL;
  init(n);
  FWT_XOR(tmpa, n, 1), FWT_XOR(tmpb, n, 1);
  mult(n);
  FWT_XOR(tmpa, n, (Mod + 1) / 2);
  for (int i = 0; i < n; ++i) {
    write(tmpa[i]), SP;
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

void init(int n) {
  for (int i = 0; i < n; ++i) {
    tmpa[i] = a[i];
    tmpb[i] = b[i];
  }
}
void FWT_OR(int *f, int lim, int opt) {
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        f[i + j + l] = (f[i + j + l] + opt * 1ll * f[i + j] % Mod) % Mod;
      }
    }
  }
}
void FWT_AND(int *f, int lim, int opt) {
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        f[i + j] = (f[i + j] + opt * 1ll * f[i + j + l] % Mod) % Mod;
      }
    }
  }
}
void FWT_XOR(int *f, int lim, int opt) {
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        int x = f[i + j], y = f[i + j + l];
        f[i + j] = (x + y) % Mod * 1ll * opt % Mod;
        f[i + j + l] = (x - y + Mod) % Mod * 1ll * opt % Mod;
      }
    }
  }
}
void mult(int n) {
  for (int i = 0; i < n; ++i) {
    tmpa[i] = tmpa[i] * 1ll * tmpb[i] % Mod;
  }
}
