#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

ll gcd(ll a, ll b);
ll solve(ll l, ll k, ll las);

ll m, k;
int T;

int main() {
  read(T);
  while (T--) {
    read(m), read(k);
    write(1 + solve(k - 1, k, m)), EL;
  }
  return 0;
}

ll gcd(ll a, ll b) { return (!b) ? a : gcd(b, a % b); }
ll solve(ll l, ll k, ll las) {
  ll d = gcd(las, k);
  if (d == 1 || l <= k / d) {
    return l;
  }
  if (k <= (double)m * (k - l)) {
    return k / d;
  }
  return m / d * (k - l) + solve((k - m * (k - l)) / d, k / d, d);
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
