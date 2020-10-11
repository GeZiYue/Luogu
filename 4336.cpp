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

const int N = 18;
const int Mod = 1000000007;

int pow(int a, int b, int m);
int calc(int n);

int f[N][N];
std::vector<pii> V[N];
int siz[1 << N];
int n, S;

int main () {
  read(n);
  S = 1 << (n - 1);
  for (int i = 1; i < S; ++i) {
    siz[i] = siz[i >> 1] + (i & 1);
  }
  for (int i = 1; i < n; ++i) {
    int m;
    read(m);
    for (int j = 1; j <= m; ++j) {
      int u, v;
      read(u), read(v);
      V[i].push_back(pii(u, v));
    }
  }
  int ans = 0;
  for (int i = 1; i < S; ++i) {
    for (int j = 1; j < n; ++j) {
      for (int k = 1; k < n; ++k) {
        f[j][k] = 0;
      }
    }
    for (int j = 1; j < n; ++j) {
      if ((i >> (j - 1)) & 1) {
        for (auto k : V[j]) {
          --f[k.first][k.second];
          --f[k.second][k.first];
          ++f[k.first][k.first];
          ++f[k.second][k.second];
        }
      }
    }
    ans = (ans + (((n - 1 - siz[i]) & 1) ? (Mod - 1) : 1) * 1ll * calc(n) % Mod) % Mod;
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
int calc(int n) {
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      f[i][j] = (f[i][j] % Mod + Mod) % Mod;
    }
  }
  int ans = 1;
  for (int i = 1; i < n; ++i) {
    int tmp = 0;
    for (int j = i; j < n; ++j) {
      if (f[j][i]) {
        tmp = j;
        break;
      }
    }
    if (!tmp) {
      return 0;
    }
    if (tmp != i) {
      ans = Mod - ans;
      std::swap(f[i], f[tmp]);
    }
    int iv = pow(f[i][i], Mod - 2, Mod);
    for (int j = i + 1; j < n; ++j) {
      int tmp = iv * 1ll * f[j][i] % Mod;
      for (int k = i; k < n; ++k) {
        f[j][k] = (f[j][k] - f[i][k] * 1ll * tmp % Mod + Mod) % Mod;
      }
    }
  }
  for (int i = 1; i < n; ++i) {
    ans = ans * 1ll * f[i][i] % Mod;
  }
  return ans;
}
