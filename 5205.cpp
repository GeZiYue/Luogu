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
const int N = 280000;
const int Mod = 998244353, g = 3, gi = 332748118;
const int iv2 = 499122177;

class Poly {
public:
  int *a;
  int deg;
  Poly() { a = new int[N]; memset(a, 0, sizeof(int) * (N - 1)); }
  void NTT(int, bool) const;
  Poly inv() const;
  Poly sqrt() const;
};
int pow(int, int, int);

int r[N];
int n;

int main () {
  Poly f;
  read(n);
  --n;
  f.deg = n;
  for (int i = 0; i <= n; ++i) {
    read(f.a[i]);
  }
  Poly g = f.sqrt();
  for (int i = 0; i <= n; ++i) {
    write(g.a[i]), SP;
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

int pow(int a, int b, int p) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % p;
    }
    now = now * 1ll * now % p;
    b >>= 1;
  }
  return ans;
}
void Poly::NTT(int lim, bool opt) const {
  for (int i = 0; i < lim; ++i) {
    if (i < r[i]) {
      std::swap(a[i], a[r[i]]);
    }
  }
  for (int l = 1; l < lim; l <<= 1) {
    int gn = pow(opt ? gi : g, (Mod - 1) / (l << 1), Mod);
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0, gw = 1; j < l; ++j, gw = gw * 1ll * gn % Mod) {
        int x = a[i + j], y = a[i + j + l] * 1ll * gw % Mod;
        a[i + j] = (x + y) % Mod;
        a[i + j + l] = (x - y + Mod) % Mod;
      }
    }
  }
}
Poly Poly::inv() const {
  Poly A, B;
  Poly ans;
  ans.a[0] = pow(this->a[0], Mod - 2, Mod);
  int now = 1;
  while ((now >> 1) <= this->deg) {
    ans.deg = now - 1;
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
      B.a[i] = ans.a[i];
    }
    for (int i = 0; i < (now << 1); ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(now << 1, false), B.NTT(now << 1, false);
    for (int i = 0; i < (now << 1); ++i) {
      ans.a[i] = B.a[i] * 1ll * ((2 - int(A.a[i] * 1ll * B.a[i] % Mod) + Mod) % Mod) % Mod;
    }
    ans.NTT(now << 1, true);
    int iv = pow(now << 1, Mod - 2, Mod);
    for (int i = 0; i < now; ++i) {
      ans.a[i] = ans.a[i] * 1ll * iv % Mod;
    }
    for (int i = now; i < (now << 1); ++i) {
      ans.a[i] = 0;
    }
    now <<= 1;
  }
  ans.deg = this->deg;
  return ans;
}
Poly Poly::sqrt() const {
  Poly A, B;
  Poly ans;
  ans.a[0] = 1;
  int now = 1;
  while ((now >> 1) <= this->deg) {
    ans.deg = now - 1;
    for (int i = 0; i < now; ++i) {
      A.a[i] = this->a[i];
    }
    B = ans.inv();
    for (int i = 0; i < (now << 1); ++i) {
      r[i] = (r[i >> 1] >> 1) | ((i & 1) * now);
    }
    A.NTT(now << 1, false), B.NTT(now << 1, false);
    for (int i = 0; i < (now << 1); ++i) {
      A.a[i] = A.a[i] * 1ll * B.a[i] % Mod;
    }
    A.NTT(now << 1, true);
    int iv = pow(now << 1, Mod - 2, Mod);
    for (int i = 0; i < now; ++i) {
      ans.a[i] = (int(A.a[i] * 1ll * iv % Mod) + ans.a[i]) % Mod * 1ll * iv2 % Mod;
    }
    for (int i = now; i < (now << 1); ++i) {
      ans.a[i] = 0;
    }
    now <<= 1;
  }
  ans.deg = this->deg;
  return ans;
}
