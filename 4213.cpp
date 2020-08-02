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
#include <unordered_map>

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

const int N = 2000000;

ll getphi(int);
ll getmu(int);

bool isp[N + 5];
int pri[N + 5], id;
ll phi[N + 5], mu[N + 5];
std::unordered_map<int, ll> ansp, ansm;
int t;

int main () {
  phi[1] = mu[1] = 1;
  for (int i = 2; i <= N; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
      mu[i] = -1;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= id && i * pri[j] <= N; ++j) {
      isp[i * pri[j]] = true;
      if (i % pri[j]) {
        mu[i * pri[j]] = -mu[i];
        phi[i * pri[j]] = phi[i] * (pri[j] - 1);
      } else {
        mu[i * pri[j]] = 0;
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
    }
  }
  for (int i = 2; i <= N; ++i) {
    mu[i] += mu[i - 1];
    phi[i] += phi[i - 1];
  }
  int t;
  read(t);
  while (t--) {
    int n;
    read(n);
    write(getphi(n)), SP, write(getmu(n)), EL;
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

ll getphi(int n) {
  if (n <= N) {
    return phi[n];
  }
  if (ansp.count(n)) {
    return ansp[n];
  }
  ll ans = 0;
  for (ll l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans += (r - l + 1) * getphi(n / l);
  }
  return ansp[n] = n * 1ull * (n + 1ll) / 2 - ans;
}
ll getmu(int n) {
  if (n <= N) {
    return mu[n];
  }
  if (ansm.count(n)) {
    return ansm[n];
  }
  ll ans = 0;
  for (ll l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans += (r - l + 1) * getmu(n / l);
  }
  return ansm[n] = 1 - ans;
}
