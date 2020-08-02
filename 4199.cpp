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
const int Mod = 1000000007;
const double PI = acos(-1);

class Complex {
public:
  double rel, img;
  Complex(double rel = 0, double img = 0) : rel(rel), img(img) {}
  friend Complex operator + (Complex i, Complex j) {
    return Complex(i.rel + j.rel, i.img + j.img);
  }
  friend Complex operator - (Complex i, Complex j) {
    return Complex(i.rel - j.rel, i.img - j.img);
  }
  friend Complex operator * (Complex i, Complex j) {
    return Complex(i.rel * j.rel - i.img * j.img, i.rel * j.img + i.img * j.rel);
  }
};
class Poly {
public:
  Complex a[N << 2];
  void FFT(int, int);
};

int pow(int, int, int);

Poly A, B;
int r[N << 2];
char ch[N];
char str[N << 1];
int tot;
int p[N << 1];
int n;

int main () {
  scanf("%s", ch + 1);
  n = strlen(ch + 1);
  for (int i = 1; i <= n; ++i) {
    A.a[i] = Complex(ch[i] == 'a', 0);
    B.a[i] = Complex(ch[i] == 'b', 0);
  }
  int lim = 1;
  while (lim <= (n << 1)) {
    lim <<= 1;
  }
  for (int i = 0; i < lim; ++i) {
    r[i] = (r[i >> 1] >> 1) | ((i & 1) * (lim >> 1));
  }
  A.FFT(lim, 1), B.FFT(lim, 1);
  for (int i = 0; i < lim; ++i) {
    A.a[i] = A.a[i] * A.a[i];
    B.a[i] = B.a[i] * B.a[i];
  }
  A.FFT(lim, -1), B.FFT(lim, -1);
  int ans = 0;
  for (int i = 1; i <= (n << 1); ++i) {
    ans = (ans + pow(2, int((A.a[i].rel + B.a[i].rel + 1) / 2), Mod) - 1) % Mod;
  }
  str[0] = '$';
  str[tot = 1] = '#';
  for (int i = 1; i <= n; ++i) {
    str[++tot] = ch[i];
    str[++tot] = '#';
  }
  str[++tot] = '%';
  int mx = 0, mid = 0;
  for (int i = 1; i < tot; ++i) {
    p[i] = (mx > i) ? min(p[2 * mid - i], mx - i) : 1;
    while (str[i + p[i]] == str[i - p[i]]) {
      ++p[i];
    }
    if (i + p[i] > mx) {
      mx = i + p[i];
      mid = i;
    }
  }
  for (int i = 2; i < tot - 1; ++i) {
    ans = (ans - p[i] / 2 + Mod) % Mod;
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

void Poly::FFT(int lim, int opt) {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    Complex gw(cos(PI / l), opt * sin(PI / l));
    for (int i = 0; i < lim; i += (l << 1)) {
      Complex gn(1);
      for (int j = 0; j < l; ++j, gn = gn * gw) {
        Complex x = a[i | j], y = a[i | j | l] * gn;
        a[i | j] = x + y;
        a[i | j | l] = x - y;
      }
    }
  }
  if (opt == -1) {
    for (int i = 0; i < lim; ++i) {
      a[i].rel = int(a[i].rel / lim + 0.5);
    }
  }
}
int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
