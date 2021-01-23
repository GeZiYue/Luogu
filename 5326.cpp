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

constexpr int N = 105;
constexpr int M = 50005;
constexpr int Mod = 998244353;

void add(int &x, int y) { (x += y) >= Mod ? x -= Mod : x; }

bool a[N];
int p[N];
int dp[2][M];
int inv[M];
int n;

int main() {
  read(n);
  for (int i = 1; i <= n; ++i) read(a[i]);
  for (int i = 1; i <= n; ++i) read(p[i]);
  dp[0][0] = 1;
  int sz = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = sz; j >= 0; --j) {
      add(dp[a[i]][j + p[i]], dp[0][j]);
      add(dp[!a[i]][j + p[i]], dp[1][j]);
    }
    sz += p[i];
  }
  inv[1] = 1;
  for (int i = 2; i <= sz; ++i) {
    inv[i] = 1ll * (Mod - Mod / i) * inv[Mod % i] % Mod;
  }
  int ans = 0;
  for (int i = 1; i <= sz; ++i) {
    add(ans, 1ll * inv[i] * dp[1][i] % Mod);
  }
  write(1ll * ans * sz % Mod), EL;
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
