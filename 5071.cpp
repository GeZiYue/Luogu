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
#include <random>
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

const int N = 100005;
const int Mod = 19260817;
const int chk[] = {6, 2, 3, 7, 59};

void getp(int);
bool miller_rabin(int);
int pollard_rho(int, int);
int fac(int);
void add(int);
void del(int);

int B;
class Query {
 public:
  int l, r;
  int id;
  friend bool operator<(const Query &i, const Query &j) {
    return (i.l / B == j.l / B) ? (i.r < j.r) : (i.l < j.l);
  }
} Q[N];
int p[N], id;
bool isp[N];
int a[N], b[N];
int sm[170][N];
int inv[N << 1];
int tot[N << 1], m;
int cnt[N << 1];
int ans[N], now;
int n, q;
std::mt19937 rnd(19260817);

int main() {
  File("5071");
  getp(1000);
  read(n), read(q);
  inv[1] = 1;
  for (int i = 2; i <= (n << 1); ++i) {
    inv[i] = (Mod - Mod / i) * 1ll * inv[Mod % i] % Mod;
  }
  B = int(sqrt(n));
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
    for (int j = 1; j <= id; ++j) {
      int k = 0;
      while (a[i] % p[j] == 0) {
        a[i] /= p[j];
        ++k;
      }
      sm[j][i] = sm[j][i - 1] + k;
    }
    if (a[i] != 1) {
      if (miller_rabin(a[i])) {
        tot[++m] = a[i];
      } else {
        tot[++m] = b[i] = fac(a[i]);
        tot[++m] = a[i] = a[i] / b[i];
      }
    } else {
      a[i] = 0;
    }
  }
  sort(tot + 1, tot + m + 1);
  m = std::unique(tot + 1, tot + m + 1) - tot - 1;
  for (int i = 1; i <= m; ++i) {
    cnt[i] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    if (a[i]) {
      a[i] = std::lower_bound(tot + 1, tot + m + 1, a[i]) - tot;
    }
    if (b[i]) {
      b[i] = std::lower_bound(tot + 1, tot + m + 1, b[i]) - tot;
    }
  }
  for (int i = 1; i <= q; ++i) {
    read(Q[i].l), read(Q[i].r);
    Q[i].id = i;
  }
  sort(Q + 1, Q + q + 1);
  int l = 1, r = 0;
  now = 1;
  for (int i = 1; i <= q; ++i) {
    while (l > Q[i].l) {
      add(--l);
    }
    while (r < Q[i].r) {
      add(++r);
    }
    while (l < Q[i].l) {
      del(l++);
    }
    while (r > Q[i].r) {
      del(r--);
    }
    int &anow = ans[Q[i].id];
    anow = now;
    for (int j = 1; j <= id; ++j) {
      anow = anow * 1ll * (sm[j][r] - sm[j][l - 1] + 1) % Mod;
    }
  }
  for (int i = 1; i <= q; ++i) {
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

void getp(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      p[++id] = i;
    }
    for (int j = 1; j <= id && p[j] * i <= n; ++j) {
      isp[p[j] * i] = true;
      if (i % p[j] == 0) {
        break;
      }
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
bool miller_rabin(int n) {
  if (n <= 1) {
    return false;
  }
  for (int i = 1; i <= chk[0]; ++i) {
    if (n % chk[i] == 0) {
      return n == chk[i];
    }
  }
  int m = n - 1;
  int r = 0;
  while ((~m) & 1) {
    ++r;
    m >>= 1;
  }
  for (int i = 1; i <= chk[0]; ++i) {
    int x = pow(chk[i], m, n);
    for (int j = 1; j <= r; ++j) {
      int y = x * 1ll * x % Mod;
      if (y == 1 && x != 1 && x != (n - 1)) {
        return false;
      }
      x = y;
    }
    if (x != 1) {
      return false;
    }
  }
  return true;
}
int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int f(int x, int c, int n) { return (x * 1ll * x % n + c) % n; }
int pollard_rho(int n, int c) {
  int l, r;
  l = r = rnd() % (n - 1) + 1;
  for (int len = 2;; len <<= 1, l = r) {
    int v = 1;
    for (int i = 1; i <= len; ++i) {
      r = f(r, c, n);
      v = v * 1ll * abs(r - l) % n;
      if (i % 32 == 0) {
        int k = gcd(v, n);
        if (k > 1) {
          return k;
        }
      }
    }
    int k = gcd(v, n);
    if (k > 1) {
      return k;
    }
  }
}
int fac(int n) {
  int c = 23333;
  while (true) {
    int k = pollard_rho(n, c--);
    if (k != n) {
      return k;
    }
  }
}
void add(int x) {
  if (a[x]) {
    now = now * 1ll * inv[cnt[a[x]]] % Mod;
    now = now * 1ll * (++cnt[a[x]]) % Mod;
  }
  if (b[x]) {
    now = now * 1ll * inv[cnt[b[x]]] % Mod;
    now = now * 1ll * (++cnt[b[x]]) % Mod;
  }
}
void del(int x) {
  if (a[x]) {
    now = now * 1ll * inv[cnt[a[x]]] % Mod;
    now = now * 1ll * (--cnt[a[x]]) % Mod;
  }
  if (b[x]) {
    now = now * 1ll * inv[cnt[b[x]]] % Mod;
    now = now * 1ll * (--cnt[b[x]]) % Mod;
  }
}
