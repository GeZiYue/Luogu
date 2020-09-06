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

typedef long double ld;
const int N = 70000;
const ld pi = acos(-1);
const ld eps = 1e-8;
const ld sq2 = sqrt(2);

class Poly {
public:
  std::complex<ld> a[N];
  void FFT(int lim, int opt);
};

std::complex<ld> qpow(std::complex<ld> a, int b);

int r[N];
Poly F;
ld sum[N];
int T;

int main () {
  int lim = 65536;
  for (int i = 1; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  std::cout.precision(10);
  read(T);
  while (T--) {
    int x, y;
    read(x), read(y);
    if ((x - 1) * y <= 30000) {
      for (int i = 0; i < lim; ++i) {
        F.a[i] = 0;
      }
      for (int i = 0; i < x; ++i) {
        F.a[i] = 1.0 / x;
      }
      F.FFT(lim, 1);
      for (int i = 0; i < lim; ++i) {
        F.a[i] = qpow(F.a[i], y);
      }
      F.FFT(lim, -1);
      sum[0] = F.a[0].real();
      for (int i = 1; i <= (x - 1) * y; ++i) {
        sum[i] = sum[i - 1] + F.a[i].real();
      }
      for (int i = 1; i <= 10; ++i) {
        int a, b;
        read(a), read(b);
        if (a == 0) {
          std::cout << std::fixed << sum[b] << std::endl;
        } else {
          std::cout << std::fixed << sum[b] - sum[a - 1] << std::endl;
        }
      }
    } else {
      ld mu = (x - 1) / 2.0 * y;
      ld sigma = sqrt((x * x - 1) / 12.0 * y);
      for (int i = 1; i <= 10; ++i) {
        int a, b;
        read(a), read(b);
        std::cout << std::fixed << (std::erf((b - mu) / sigma / sq2) - std::erf((a - 0.5 - mu) / sigma / sq2)) / 2 << std::endl;
      }
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

void Poly::FFT(int lim, int opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std:;swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    std::complex<ld> gn(cos(pi / l), opt * sin(pi / l));
    for (int i = 0; i < lim; i += (l << 1)) {
      std::complex<ld> gw(1, 0);
      for (int j = 0; j < l; ++j) {
        std::complex<ld> x = a[i | j], y = a[i | j | l] * gw;
        a[i | j] = x + y;
        a[i | j | l] = x - y;
        gw *= gn;
      }
    }
  }
  if (!~opt) {
    for (int i = 0; i < lim; ++i) {
      a[i] /= lim;
    }
  }
}
std::complex<ld> qpow(std::complex<ld> a, int b) {
  std::complex<ld> now = a, ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * now;
    }
    now = now * now;
    b >>= 1;
  }
  return ans;
}
