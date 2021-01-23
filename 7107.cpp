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

constexpr int N = 100005;

ll x[N], y[N];

int main() {
  ll n, m, k, p;
  read(n), read(m), read(k), read(p);
  ll q = std::min(m, k / p);
  for (int i = 1; i <= p; ++i) {
    x[i] = q, y[i] = m - q, k -= q;
  }
  if (n == p) {
    if (k) {
      puts("NO");
    } else {
      puts("YES");
      for (int i = 1; i <= n; ++i) {
        write(x[i]), SP, write(y[i]), EL;
      }
    }
    return 0;
  }
  q = k / (n - p);
  if (q >= x[1] || q > m) {
    puts("NO");
    return 0;
  }
  for (int i = p + 1; i <= n; ++i) {
    x[i] = q, y[i] = m - q, k -= q;
  }
  for (int i = n; i >= n - k + 1; --i) {
    ++x[i], --y[i];
    if (x[i] >= x[1]) {
      puts("NO");
      return 0;
    }
  }
  puts("YES");
  for (int i = 1; i <= n; ++i) {
    write(x[i]), SP, write(y[i]), EL;
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
