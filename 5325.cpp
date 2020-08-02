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
const int Mod = 1000000007;
const int iv3 = 333333336;

void getp(int);
void getg(ll);
int S(ll, int);

bool isp[N];
int pri[N], id;
int sp1[N], sp2[N];
ll num[N * 10];
int g1[N * 10], g2[N * 10];
int id1[N], id2[N], tot;
int Sq;
ll n;

int main () {
  read(n);
  Sq = int(sqrt(n));
  getp(Sq);
  getg(n);
  write((S(n, 0) + 1) % Mod), EL;
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

void getp(int n) {
  pri[0] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
      sp1[id] = (sp1[id - 1] + i) % Mod;
      sp2[id] = (sp2[id - 1] + i * 1ll * i % Mod) % Mod;
    }
    for (int j = 1; j <= id && pri[j] * i <= n; ++j) {
      isp[pri[j] * i] = true;
      if (i % pri[j] == 0) {
        break;
      }
    }
  }
}
void getg(ll n) {
  for (ll l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    num[++tot] = n / l;
    g1[tot] = num[tot] % Mod * (num[tot] % Mod + 1) / 2 % Mod;
    g2[tot] = g1[tot] * 1ll * ((2 * num[tot] % Mod + 1) % Mod) % Mod * iv3 % Mod;
    if (g1[tot]) {
      --g1[tot];
    } else {
      g1[tot] = Mod - 1;
    }
    if (g2[tot]) {
      --g2[tot];
    } else {
      g2[tot] = Mod - 1;
    }
    ((num[tot] <= Sq) ? (id1[num[tot]]) : (id2[n / num[tot]])) = tot;
  }
  for (int i = 1; i <= id; ++i) {
    for (int j = 1; j <= tot && pri[i] * 1ll * pri[i] <= num[j]; ++j) {
      int k = (num[j] / pri[i] <= Sq) ? id1[num[j] / pri[i]] : id2[n / (num[j] / pri[i])];
      g1[j] = (g1[j] - pri[i] * 1ll * (g1[k] - sp1[i - 1] + Mod) % Mod + Mod) % Mod;
      g2[j] = (g2[j] - pri[i] * 1ll * pri[i] % Mod * (g2[k] - sp2[i - 1] + Mod) % Mod + Mod) % Mod;
    }
  }
}
int S(ll x, int k) {
  if (pri[k] >= x) {
    return 0;
  }
  int now = x <= Sq ? id1[x] : id2[n / x];
  int ans = (1ll * g2[now] - g1[now] + Mod + sp1[k] - sp2[k] + Mod) % Mod;
  for (int i = k + 1; i <= id && pri[i] * 1ll * pri[i] <= x; ++i) {
    ll j = pri[i];
    for (int c = 1; j <= x; ++c, j = j * pri[i]) {
      ll q = j % Mod;
      ans = (ans + q * (q - 1) % Mod * (S(x / j, i) + (c > 1)) % Mod) % Mod;
    }
  }
  return ans;
}
