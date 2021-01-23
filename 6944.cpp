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

constexpr int N = 505;

double C[N * 2][N];
double f[N][N];
int n, d, r;

int main() {
  C[0][0] = 1;
  for (int i = 1; i <= 1000; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= 500; ++j) {
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]);
    }
  }
  read(n), read(d), read(r);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= d; ++j) {
      for (int k = 0; k <= std::min(i, j); ++k) {
        f[i][j] += C[i][k] * (f[k][j - k] + C[j - 1][k - 1] * std::min(r, k));
      }
    }
  }
  std::cout.precision(8);
  std::cout << std::fixed << f[n][d] / C[n + d - 1][n - 1] + r << std::endl;
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
