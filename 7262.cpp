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

constexpr int N = 105;

char ch[N][N];
char dir;
int n, m;

int main() {
  read(n), read(m);
  std::cin >> dir;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      std::cin >> ch[i][j];
    }
  }
  bool flag = true;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (ch[i][j] == 'o') {
        if (dir == '^') {
          int ii = i, jj = j;
          for (; ii >= 1; --ii) {
            if (ch[ii][jj] == 'x') {
              flag = false;
            }
          }
        }
        if (dir == 'v') {
          int ii = i, jj = j;
          for (; ii <= n; ++ii) {
            if (ch[ii][jj] == 'x') {
              flag = false;
            }
          }
        }
        if (dir == '<') {
          int ii = i, jj = j;
          for (; jj >= 1; --jj) {
            if (ch[ii][jj] == 'x') {
              flag = false;
            }
          }
        }
        if (dir == '>') {
          int ii = i, jj = j;
          for (; jj <= m; ++jj) {
            if (ch[ii][jj] == 'x') {
              flag = false;
            }
          }
        }
      }
    }
  }
  puts(flag ? "OK" : "GG");
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
