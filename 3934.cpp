#include <unordered_set>
#include <unordered_map>
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
const int N = 500005;
const int M = 20000005;

class Ans {
public:
  int res;
  bool flag;
  inline Ans(int r, bool f) : res(r), flag(f) {}
};

void getphi(int);
void update(int, int, int);
Ans query(int, int, int);

bool isp[M];
int phi[M];
int pri[M / 10], id;
ll BIT[N];
int Siz;

int main () {
  getphi(20000000);
  int n, m;
  read(n), read(m);
  Siz = n + 1;
  for (int i = 1; i <= n; ++i) {
    int a;
    read(a);
    update(i, i, a);
  }
  for (int i = 1; i <= m; ++i) {
    int type, l, r, x;
    read(type), read(l), read(r), read(x);
    if (type == 1) {
      update(l, r, x);
    } else {
      write(query(l, r, x).res), EL;
    }
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

inline void getphi(int n) {
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
      }
      phi[i * pri[j]] = phi[i] * (pri[j] - 1);
    }
  }
}
inline ll query(int x) {
  ll ans = 0;
  while (x) {
    ans += BIT[x];
    x -= (x & (-x));
  }
  return ans;
}
inline void update(int x, int num) {
  while (x <= Siz) {
    BIT[x] += num;
    x += (x & (-x));
  }
}
inline void update(int l, int r, int num) {
  update(l, num);
  update(r + 1, -num);
}
inline Ans pow(ll a, int b, int m) {
  Ans now(a % m, a >= m), ans(1, false);
  ll tmp;
  while (b) {
    if (b & 1) {
      tmp = ans.res * 1ll * now.res;
      if (tmp >= m) {
        ans.flag = true;
      }
      if (now.flag) {
        ans.flag = true;
      }
      ans.res = tmp % m;
    }
    tmp = now.res * 1ll * now.res;
    if (tmp >= m) {
      now.flag = true;
    }
    now.res = tmp % m;
    b >>= 1;
  }
  return ans;
}
Ans query(int l, int r, int m) {
  ll now = query(l);
  if (m == 1) {
    return Ans(0, true);
  }
  if (now == 1) {
    return Ans(1, false);
  }
  if (l == r) {
    return Ans(now % m, now >= m);
  }
  Ans ans = query(l + 1, r, phi[m]);
  if (ans.flag) {
    ans.res += phi[m];
  }
  return pow(now, ans.res, m);
}
