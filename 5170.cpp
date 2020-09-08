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

const int Mod = 998244353;
const int inv2 = (Mod + 1) / 2, inv3 = (Mod + 1) / 3;

class Ans {
public:
  int f, g, h;
};

Ans work(int a, int b, int c, int n);

int main () {
  int t;
  read(t);
  while (t--) {
    int a, b, c, n;
    read(n), read(a), read(b), read(c);
    Ans ans = work(a, b, c, n);
    write(ans.f), SP, write(ans.g), SP, write(ans.h), EL;
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

inline int qs(int n) {
  return n + 1;
}
inline int qsum(int n) {
  return n * 1ll * (n + 1) / 2 % Mod;
}
inline int qssum(int n) {
  return n * 1ll * (n + 1) / 2 % Mod * (2 * n + 1) % Mod * inv3 % Mod;
}
Ans work(int a, int b, int c, int n) {
  Ans ans;
  if (a == 0) {
    ans.f = qs(n) * 1ll * (b / c) % Mod;
    ans.g = qs(n) * 1ll * (b / c) % Mod * (b / c) % Mod;
    ans.h = qsum(n) * 1ll * (b / c) % Mod;
  } else {
    if (a >= c || b >= c) {
      Ans tmp = work(a % c, b % c, c, n);
      ans.f = (tmp.f + qsum(n) * 1ll * (a / c) % Mod + qs(n) * 1ll * (b / c) % Mod) % Mod;
      ans.g = (tmp.g + (a / c) * 2ll * tmp.h % Mod + (b / c) * 2ll * tmp.f % Mod + qssum(n) * 1ll * (a / c) % Mod * (a / c) % Mod +
        qsum(n) * 2ll * (a / c) % Mod * (b / c) % Mod + qs(n) * 1ll * (b / c) % Mod * (b / c) % Mod) % Mod;
      ans.h = (tmp.h + qssum(n) * 1ll * (a / c) % Mod + qsum(n) * 1ll * (b / c) % Mod) % Mod;
    } else {
      int m = (a * 1ll * n + b) / c;
      Ans tmp = work(c, c - b - 1, a, m - 1);
      ans.f = (n * 1ll * m % Mod - tmp.f + Mod) % Mod;
      ans.g = ((n * 1ll * m % Mod * (m + 1) % Mod - ans.f - tmp.h * 2ll % Mod - tmp.f * 2ll % Mod) % Mod + Mod) % Mod;
      ans.h = ((m * 1ll * n % Mod * (n + 1) % Mod - tmp.g - tmp.f) % Mod + Mod) * inv2 % Mod;
    }
  }
  return ans;
}
