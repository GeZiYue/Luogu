#include <bits/stdc++.h>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <typename T>
void read(T &);
template <typename T>
void write(const T &);

typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;

constexpr int N = 1005;

int col(int a, int b) { return (a / 4 == b / 4) ? 1 : ((a / 16 == b / 16) ? 2 : 3); }

ll x[N];
int h[N];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) {
    read(x[i]);
  }
  for (int i = 1; i <= n; ++i) {
    h[i] = 63 - __builtin_clzll(x[i]);
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = 1; j < i; ++j) {
      if (x[i] % x[j] == 0) {
        write(col(h[i], h[j])), SP;
      } else {
        write(1), SP;
      }
    }
    EL;
  }
  return 0;
}

template <typename T>
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
template <typename T>
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
