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

const int N = 100005;
const int Mod = 100003;

std::vector<int> fac[N];
bool sta[N];
int f[N];
int inv[N];
int n, k;

int main () {
  read(n), read(k);
  for (int i = 1; i <= n; ++i) {
    read(sta[i]);
  }
  inv[1] = 1;
  int fact = 1;
  for (int i = 2; i <= n; ++i) {
    fact = fact * 1ll * i % Mod;
    inv[i] = (Mod - Mod / i) * 1ll * inv[Mod % i] % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i; j <= n; j += i) {
      fac[j].push_back(i);
    }
  }
  int beg = 0;
  for (int i = n; i >= 1; --i) {
    if (sta[i]) {
      for (auto j : fac[i]) {
        sta[j] ^= 1;
      }
      ++beg;
    }
  }
  for (int i = 1; i <= k; ++i) {
    f[i] = 1;
  }
  f[n] = 1;
  for (int i = n - 1; i > k; --i) {
    f[i] = (n + (n - i) * 1ll * f[i + 1] % Mod) * inv[i] % Mod;
  }
  int ans = 0;
  for (int i = 1; i <= beg; ++i) {
    ans = (ans + f[i]) % Mod;
  }
  write(ans * 1ll * fact % Mod), EL;
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
