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

const int N = 1000005;

void init(int);
int pow(int, int, int);
int gcd(int, int);

bool isp[N];
int pri[N], phi[N], id;
bool hvg[N];
int p[1005], cnt;
int g[N], num;

int main () {
  init(1000000);
  int t;
  read(t);
  while (t--) {
    int n, d;
    read(n), read(d);
    if (!hvg[n]) {
      write(0), EL, EL;
      continue;
    }
    {
      cnt = 0;
      for (int i = 1; i <= id && pri[i] <= phi[n]; ++i) {
        if (phi[n] % pri[i] == 0) {
          p[++cnt] = pri[i];
        }
      }
    }
    int mn;
    for (int i = 1; ; ++i) {
      bool flag = pow(i, phi[n], n) == 1;
      for (int j = 1; j <= cnt && flag; ++j) {
        if (pow(i, phi[n] / p[j], n) == 1) {
          flag = false;
        }
      }
      if (flag) {
        mn = i;
        break;
      }
    }
    num = 0;
    for (int i = 1, prd = 1; i <= phi[n]; ++i) {
      prd = prd * 1ll * mn % n;
      if (gcd(i, phi[n]) == 1) {
        g[++num] = prd;
      }
    }
    sort(g + 1, g + num + 1);
    write(num), EL;
    for (int i = 1; i <= (num / d); ++i) {
      write(g[i * d]), SP;
    }
    EL;
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

void init(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= id && i * pri[j] <= n; ++j) {
      isp[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      } else {
        phi[i * pri[j]] = phi[i] * (pri[j] - 1);
      }
    }
  }
  hvg[2] = hvg[4] = true;
  for (int i = 2; i <= id; ++i) {
    hvg[pri[i]] = true;
    if ((pri[i] << 1) <= n) {
      hvg[pri[i] << 1] = true;
    }
    if (pri[i] * 1ll * pri[i] <= n) {
      for (int j = pri[i] * pri[i]; j <= n; j *= pri[i]) {
        hvg[j] = true;
        if ((j << 1) <= n) {
          hvg[j << 1] = true;
        }
      }
    }
  }
}
int pow(int a, int b, int m) {
  int ans = 1 % m, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}
