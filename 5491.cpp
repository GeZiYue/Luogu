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
#include <random>

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

int mod, si;

class Complex {
public:
  int rel, img;
  inline Complex(int real = 0, int imag = 0) : rel(real), img(imag) {}
  inline Complex operator *(const Complex i) const {
    return Complex(
      (this->rel * 1ll * i.rel % mod + si * 1ll * this->img % mod * i.img % mod) % mod,
      (this->rel * 1ll * i.img % mod + this->img * 1ll * i.rel % mod) % mod
    );
  }
};

int pow(int, int, int);
void calc(int, int);

int main () {
  int t;
  read(t);
  while (t--) {
    int n, p;
    read(n), read(p);
    calc(n, p);
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

inline int pow(int a, int b, int p) {
  int now = a, ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % p;
    }
    now = now * 1ll * now % p;
    b >>= 1;
  }
  return ans;
}
inline Complex pow(Complex a, int b) {
  Complex now = a, ans = 1;
  while (b) {
    if (b & 1) {
      ans = ans * now;
    }
    now = now * now;
    b >>= 1;
  }
  return ans;
}
inline bool check(int n, int p) {
  return pow(n, (p - 1) / 2, p) == 1;
}
inline void calc(int n, int p) {
  if (!n) {
    write(0), EL;
    return;
  }
  if (!check(n, p)) {
    puts("Hola!");
    return;
  }
  std::mt19937 rnd;
  int a = (rnd() % p + p) % p;
  while (!a || check((a * 1ll * a % p + p - n) % p, p)) {
    a = (rnd() % p + p) % p;
  }
  mod = p, si = (a * 1ll * a % p + p - n) % p;
  int ans1 = pow(Complex(a, 1), (p + 1) / 2).rel, ans2 = p - ans1;
  if (ans1 > ans2) {
    ans1 ^= ans2 ^= ans1 ^= ans2;
  }
  write(ans1), SP;
  if (ans1 != ans2) {
    write(ans2), SP;
  }
  EL;
}
