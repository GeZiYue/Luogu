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
using std::sort;

const int N = 250000;
const int Mod = 1000000007, iv2 = 500000004;

int pow(int a, int b, int m);
void add(int &a, int b) { ((a += b) >= Mod) ? (a -= Mod) : a; }
void sub(int &a, int b) { ((a -= b) < 0) ? (a += Mod) : a; }
int C(int n, int m);
int iC(int n, int m);

class Query {
 public:
  int n, k, id;
  Query(int n = 0, int k = 0, int id = 0) : n(n), k(k), id(id) {}
} q[N];

int fac[N + 5], ifac[N + 5];
int T, Block;
int ans[N];
int n[N], m[N];

int main() {
  fac[0] = 1;
  for (int i = 1; i <= N; ++i) {
    fac[i] = fac[i - 1] * 1ll * i % Mod;
  }
  ifac[N] = pow(fac[N], Mod - 2, Mod);
  for (int i = N - 1; i >= 0; --i) {
    ifac[i] = ifac[i + 1] * 1ll * (i + 1) % Mod;
  }
  int p;
  read(T), read(p);
  Block = 500;
  for (int i = 1; i <= T; ++i) {
    read(n[i]), read(m[i]);
    if (n[i] >= m[i]) {
      q[i] = Query(n[i] + m[i], m[i] - 1, i);
    } else {
      q[i] = Query(n[i] + m[i], n[i] - 1, i);
    }
  }
  std::sort(q + 1, q + T + 1, [&](Query i, Query j) {
    return (i.n / Block == j.n / Block) ? (i.k < j.k) : (i.n < j.n);
  });
  int nn = 0, nk = 0, now = 1;
  for (int i = 1; i <= T; ++i) {
    while (nn < q[i].n) {
      now = now * 2 % Mod;
      sub(now, C(nn, nk));
      ++nn;
    }
    while (nk > q[i].k) {
      sub(now, C(nn, nk));
      --nk;
    }
    while (nk < q[i].k) {
      ++nk;
      add(now, C(nn, nk));
    }
    while (nn > q[i].n) {
      --nn;
      add(now, C(nn, nk));
      now = now * 1ll * iv2 % Mod;
    }
    ans[q[i].id] = now;
  }
  for (int i = 1; i <= T; ++i) {
    ans[i] = ans[i] * 1ll * iC(n[i], m[i]) % Mod;
    if (n[i] > m[i]) {
      add(ans[i], n[i] - m[i]);
    }
    write(ans[i]), EL;
  }
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
int C(int n, int m) { return fac[n] * 1ll * ifac[m] % Mod * ifac[n - m] % Mod; }
int iC(int n, int m) { return fac[n] * 1ll * fac[m] % Mod * ifac[n + m] % Mod; }
