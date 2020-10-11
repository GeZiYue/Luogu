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

const int N = 1005;
const int Mod = 998244353;

void add(int &a, int b) { a += b; if (a >= Mod) { a -= Mod; } }
void sub(int &a, int b) { a -= b; if (a < 0) { a += Mod; } }
int pow(int a, int b, int m);
int C(int n, int m);

int fac[N], ifac[N];
int f1[N], f2[N];
int n, a, b, c, d;

int main () {
  read(n), read(a), read(b), read(c), read(d);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  int k = min(min(a, b), min(min(c, d), n >> 2));
  a -= k, b -= k, c -= k, d -= k;
  for (int i = 0; i <= a; ++i) {
    for (int j = 0; j <= b; ++j) {
      add(f1[i + j], ifac[i] * 1ll * ifac[j] % Mod);
    }
  }
  for (int i = 0; i <= c; ++i) {
    for (int j = 0; j <= d; ++j) {
      add(f2[i + j], ifac[i] * 1ll * ifac[j] % Mod);
    }
  }
  int ans = 0;
  for ( ; ~k; --k) {
    int now = n - 4 * k;
    int cnt = 0;
    for (int i = 0; i <= now; ++i) {
      add(cnt, f1[i] * 1ll * f2[now - i] % Mod);
    }
    cnt = cnt * 1ll * C(now + k, k) % Mod * fac[now] % Mod;
    if (k & 1) {
      cnt = (Mod - cnt) % Mod;
    }
    add(ans, cnt);
    ++a, ++b, ++c, ++d;
    for (int i = 0; i <= a; ++i) {
      add(f1[i + b], ifac[i] * 1ll * ifac[b] % Mod);
    }
    for (int i = 0; i <= b; ++i) {
      add(f1[a + i], ifac[a] * 1ll * ifac[i] % Mod);
    }
    sub(f1[a + b], ifac[a] * 1ll * ifac[b] % Mod);
    for (int i = 0; i <= c; ++i) {
      add(f2[i + d], ifac[i] * 1ll * ifac[d] % Mod);
    }
    for (int i = 0; i <= d; ++i) {
      add(f2[c + i], ifac[c] * 1ll * ifac[i] % Mod);
    }
    sub(f2[c + d], ifac[c] * 1ll * ifac[d] % Mod);
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
int C(int n, int m) {
  return fac[n] * 1ll * ifac[m] % Mod * ifac[n - m] % Mod;
}
