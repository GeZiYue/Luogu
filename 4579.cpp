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

const int N = 10005;
typedef double ld;

ld calc();

ld f[2][N];
ld x[2][N];
ld ex[2];
int ey[2], pos[2];
ld h;
int n[2];

int main() {
  read(n[0]), read(n[1]);
  read(ey[0]), read(pos[0]), read(ey[1]), read(pos[1]);
  bool rev = 0;
  if (ey[0]) {
    rev = true;
    ey[0] ^= 1, ey[1] ^= 1;
    std::swap(n[0], n[1]);
  }
  scanf("%lf", &h);
  for (int i = 1; i <= n[rev]; ++i) scanf("%lf", x[rev] + i);
  for (int i = 1; i <= n[rev ^ 1]; ++i) scanf("%lf", x[rev ^ 1] + i);
  ex[0] = x[ey[0]][pos[0]];
  ex[1] = x[ey[1]][pos[1]];
  std::sort(x[0] + 1, x[0] + n[0] + 1);
  std::sort(x[1] + 1, x[1] + n[1] + 1);
  ld Ans = calc();
  std::reverse(x[0] + 1, x[0] + n[0] + 1);
  std::reverse(x[1] + 1, x[1] + n[1] + 1);
  for (int i = 1; i <= n[0]; ++i) x[0][i] = 20000 - x[0][i];
  for (int i = 1; i <= n[1]; ++i) x[1][i] = 20000 - x[1][i];
  ex[0] = 20000 - ex[0];
  ex[1] = 20000 - ex[1];
  Ans = std::min(Ans, calc());
  printf("%.2lf\n", Ans);
  return 0;
}

ld Dis(int i, int j) {
  ld d = x[0][i] - x[1][j];
  return std::sqrt(d * d + h * h);
}
ld End(int y, int id) {
  ld d = x[y][id] - ex[1];
  return (y == ey[1]) ? std::abs(d) : std::sqrt(d * d + h * h);
}
ld calc() {
  ld Ans = 1e30;
  for (int i = n[0]; i; --i) {
    if (i == n[0]) {
      for (int j = n[1]; j; --j) {
        if (j == n[1]) {
          f[0][j] = End(0, n[0]);
          f[1][j] = End(1, n[1]);
        } else {
          f[0][j] = std::min(Dis(i, n[1]) + x[1][n[1]] - x[1][j + 1] + End(1, j + 1),
                             f[1][j + 1] + Dis(i, j + 1));
          f[1][j] = f[1][j + 1] + x[1][j + 1] - x[1][j];
        }
      }
    } else {
      for (int j = n[1]; j; --j) {
        if (j == n[1]) {
          f[1][j] = std::min(f[0][j] + Dis(i + 1, j),
                             x[0][n[0]] - x[0][i + 1] + Dis(n[0], j) + End(0, i + 1));
          f[0][j] = x[0][n[0]] - x[0][i] + End(0, n[0]);
        } else {
          f[1][j] = std::min(f[0][j] + Dis(i + 1, j), f[1][j + 1] + x[1][j + 1] - x[1][j]);
          f[0][j] = std::min(f[0][j] + x[0][i + 1] - x[0][i], f[1][j + 1] + Dis(i, j + 1));
        }
      }
    }
    Ans = std::min(Ans, ex[0] - x[0][1] + x[0][i] - x[0][1] + Dis(i, 1) + f[1][1]);
    Ans = std::min(Ans, std::abs(ex[0] - x[0][i]) + x[0][i] - x[0][1] + Dis(1, 1) + f[1][1]);
    if (x[0][i] <= ex[0]) {
      break;
    }
  }
  return Ans;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!isNum(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (isNum(ch)) {
    k = (k << 1) + (k << 3) + ch - '0';
    ch = getchar();
  }
  Re = flag * k;
}
template <typename T>
void write(const T &Wr) {
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
