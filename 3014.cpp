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
const int N = 25;

void per(ll);
void query();

ll fac[N];
int a[N];
bool t[N];
int n;

int main () {
  int m;
  read(n), read(m);
  fac[0] = 1;
  for (int i = 1; i < n; ++i) {
    fac[i] = fac[i - 1] * i;
  }
  for (int i = 1; i <= m; ++i) {
    char ch = getchar();
    while (ch != 'P' && ch != 'Q') {
      ch = getchar();
    }
    if (ch == 'P') {
      ll x;
      read(x);
      per(x);
    } else {
      for (int j = 1; j <= n; ++j) {
        read(a[j]);
      }
      query();
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

void per(ll x) {
  memset(t, false, sizeof(t));
  --x;
  for (int i = 1; i <= n; ++i) {
    a[i] = x / fac[n - i];
    int j = 0;
    while (true) {
      ++j;
      if (t[j] == false) {
        if (!a[i]) {
          break;
        }
        --a[i];
      }
    }
    a[i] = j;
    t[j] = true;
    x %= fac[n - i];
  }
  for (int i = 1; i <= n; ++i) {
    write(a[i]), SP;
  }
  EL;
}
void query() {
  memset(t, false, sizeof(t));
  ll ans = 1;
  for (int i = 1; i <= n; ++i) {
    int now = 0;
    for (int j = i + 1; j <= n; ++j) {
      now += a[j] < a[i];
    }
    ans += now * fac[n - i];
  }
  write(ans), EL;
}
