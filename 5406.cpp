#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

const int N = 75;
const int M = 1 << 12;
const int Mod = 998244353, iv2 = (Mod + 1) / 2;

int pow(int a, int b, int m);
void FWT(int *A, int lim, bool opt);
int det(int n);

int mp[N][N][M], f[N][N];
int B[M];
char ch[15];
int n, m, l, lim;

int main() {
  read(n), read(m);
  scanf("%s", ch + 1);
  l = strlen(ch + 1);
  lim = 1 << l;
  for (int i = 1; i <= m; ++i) {
    int u, v, w;
    read(u), read(v), read(w);
    ++mp[u][u][w], ++mp[v][v][w];
    --mp[u][v][w], --mp[v][u][w];
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 1; j < n; ++j) {
      for (int k = 0; k < lim; ++k) {
        (mp[i][j][k] += Mod) %= Mod;
      }
      FWT(mp[i][j], lim, false);
    }
  }
  for (int k = 0; k < lim; ++k) {
    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < n; ++j) {
        f[i][j] = mp[i][j][k];
      }
    }
    B[k] = det(n - 1);
  }
  FWT(B, lim, true);
  for (int i = lim - 1; i >= 0; --i) {
    if (B[i]) {
      write(i), EL;
      return 0;
    }
  }
  write(-1), EL;
  return 0;
}

template <class T>
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
template <class T>
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
void FWT(int *A, int lim, bool opt) {
  for (int l = 1, now = 1; l < lim; l <<= 1, ++now) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        int x = A[i + j], y = A[i + j + l];
        if (ch[now] == '|') {
          if (opt) {
            A[i + j + l] = (y - x + Mod) % Mod;
          } else {
            A[i + j + l] = (x + y) % Mod;
          }
        } else {
          if (ch[now] == '&') {
            if (opt) {
              A[i + j] = (x - y + Mod) % Mod;
            } else {
              A[i + j] = (x + y) % Mod;
            }
          } else {
            A[i + j] = (x + y) % Mod;
            A[i + j + l] = (x - y) % Mod;
            if (opt) {
              A[i + j] = A[i + j] * 1ll * iv2 % Mod;
              A[i + j + l] = A[i + j + l] * 1ll * iv2 % Mod;
            }
          }
        }
      }
    }
  }
}
int det(int n) {
  int ans = 1;
  for (int i = 1; i <= n; ++i) {
    int now = 0;
    for (int j = i; j <= n; ++j) {
      if (f[i][j]) {
        now = j;
        break;
      }
    }
    if (!now) {
      return 0;
    }
    if (i != now) {
      std::swap(f[i], f[now]);
      ans = Mod - ans;
    }
    int iv = pow(f[i][i], Mod - 2);
    for (int j = i + 1; j <= n; ++j) {
      int tmp = iv * 1ll * f[j][i] % Mod;
      for (int k = i; k <= n; ++k) {
        f[j][k] = (f[j][k] - f[i][k] * 1ll * tmp % Mod + Mod) % Mod;
      }
    }
    ans = ans * 1ll * f[i][i] % Mod;
  }
  return ans;
}
