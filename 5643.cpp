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

constexpr int N = 20;
constexpr int M = 40;
constexpr int K = 1 << 18;
constexpr int Mod = 998244353;

void add(int u, int v);
int pow(int a, int b, int m);
void dfs(int u, int fa);
void FMT(int *a, int lim);

int hed[N], nxt[M], to[M], id;
int k[N], b[N];
int F[K], popc[K];
int now;
int n, Q, x;

int main() {
  read(n), read(Q), read(x);
  for (int i = 1; i < n; ++i) {
    int u, v;
    read(u), read(v);
    add(u, v), add(v, u);
  }
  int lim = 1 << n;
  for (int s = 1; s < lim; ++s) {
    popc[s] = (popc[s >> 1] + (s & 1));
  }
  for (int s = 0; s < lim; ++s) {
    now = s;
    dfs(x, 0);
    F[s] = (b[x] == 0 ? 0 : ((popc[s] & 1) ? b[x] : Mod - b[x]));
  }
  FMT(F, lim);
  while (Q--) {
    int m;
    read(m);
    now = 0;
    for (int i = 1; i <= m; ++i) {
      int x;
      read(x);
      now |= (1 << (x - 1));
    }
    write(F[now]), EL;
  }
  return 0;
}

void add(int u, int v) {
  nxt[++id] = hed[u];
  hed[u] = id;
  to[id] = v;
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
void dfs(int u, int fa) {
  if ((now >> (u - 1)) & 1) {
    k[u] = b[u] = 0;
    return;
  }
  int sk = 0, sb = 0;
  int deg = 0;
  for (int i = hed[u]; i; i = nxt[i]) {
    int v = to[i];
    if (v ^ fa) {
      dfs(v, u);
      sk = (sk + k[v]) % Mod;
      sb = (sb + b[v]) % Mod;
    }
    ++deg;
  }
  int iv = pow((deg - sk + Mod) % Mod, Mod - 2, Mod);
  k[u] = iv, b[u] = (deg + sb) * 1ll * iv % Mod;
}
void FMT(int *a, int lim) {
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        a[i | j | l] = (a[i | j | l] + a[i | j]) % Mod;
      }
    }
  }
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
