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

template <class T> void read(T &);
template <class T> void write(const T &);

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

const int N = 105;
const int Mod = 997;

int pow(int a, int b, int m);
int gcd(int a, int b);
void dfs(int i, int s);
void calc();

int sum[N];
int v[N], top;
int fac[N], ifac[N], inv[N];
int GCD[N][N];
int ans;
int n;

int main() {
  read(n);
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  inv[1] = 1;
  for (int i = 2; i <= n; ++i) {
    inv[i] = (Mod - Mod / i) * 1ll * inv[Mod % i] % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      GCD[i][j] = gcd(i, j);
    }
  }
  dfs(n, 0);
  ans = ans * 1ll * ifac[n] % Mod;
  write(ans), EL;
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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
int gcd(int a, int b) { return (b == 0) ? a : gcd(b, a % b); }
void dfs(int i, int s) {
  if (i == 1) {
    sum[1] = n - s;
    calc();
    return;
  }
  for (int j = 0; s + j * i <= n; ++j) {
    sum[i] = j;
    dfs(i - 1, s + i * j);
    sum[i] = 0;
  }
}
void calc() {
  int top = 0;
  int now = fac[n];
  for (int i = 1; i <= n; ++i) {
    now = now * 1ll * ifac[sum[i]] % Mod;
    for (int j = 1; j <= sum[i]; ++j) {
      v[++top] = i;
      now = now * 1ll * inv[i] % Mod;
    }
  }
  int sum = 0;
  for (int i = 1; i <= top; ++i) {
    sum = (sum + (v[i] / 2)) % (Mod - 1);
    for (int j = i + 1; j <= top; ++j) {
      sum = (sum + GCD[v[i]][v[j]]) % (Mod - 1);
    }
  }
  ans = (ans + now * 1ll * pow(2, sum, Mod) % Mod) % Mod;
}
