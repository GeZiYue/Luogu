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

const int N = 50;
const int Mod = 1000000007;

ll gcd(ll a, ll b);
int pow(int a, int b, int m);

ll f[N], l[N];
int cnt[10];
ll n;

int main () {
  l[1] = 1;
  f[2] = 1;
  for (int i = 2; i <= 42; ++i) {
    l[i] = l[i - 1] * (i / gcd(i, l[i - 1]));
  }
  for (int i = 3; i <= 43; ++i) {
    for (int j = 2; j < i; ++j) {
      if (i % j) {
        f[i] = f[j] + 1;
        break;
      }
    }
  }
  read(n);
  l[43] = n + 1;
  cnt[2] = ((n / l[1]) - 1 - (n / l[2])) % (Mod - 1);
  for (int i = 2; i <= 42; ++i) {
    cnt[f[i + 1] + 1] = (cnt[f[i + 1] + 1] + ((n / l[i]) - (n / l[i + 1])) % (Mod - 1)) % (Mod - 1);
  }
  if (cnt[3]) {
    --cnt[3];
  } else {
    cnt[3] = Mod - 2;
  }
  int ans = 1;
  for (int i = 2; i <= 6; ++i) {
    ans = ans * 1ll * pow(i, cnt[i], Mod) % Mod;
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

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
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
