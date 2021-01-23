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

constexpr int N = 2005;
constexpr int Mod = 666623333;

int pow(int a, int b, int m);

int f[N][N], sum[N][N], g[N];
int pw[N][N];
int fl[N], fr[N];
int p[N];
pii a[N], b[N];
int n, x, q;

int main() {
  for (int i = 0; i <= 2000; ++i) {
    pw[i][0] = 1;
    for (int j = 1; j <= 2000; ++j) {
      pw[i][j] = 1ll * pw[i][j - 1] * i % Mod;
    }
  }
  read(n), read(x), read(q);
  for (int i = 1; i <= q; ++i) {
    read(b[i].first), read(b[i].second);
  }
  std::sort(b + 1, b + q + 1);
  int top = 0;
  for (int i = 1; i <= q; ++i) {
    if (b[i].first == b[i - 1].first) {
      continue;
    }
    while (top && a[top].second >= b[i].second) {
      --top;
    }
    a[++top] = b[i];
  }
  q = top;
  for (int i = 1; i <= q; ++i) {
    for (int j = a[i].first; j <= a[i].second; ++j) {
      if (!fl[j]) {
        fl[j] = i;
      }
      fr[j] = i;
    }
  }
  top = 0;
  for (int i = 1; i <= n; ++i) {
    if (!fl[i]) {
      fl[i] = top + 1, fr[i] = top;
    } else {
      top = fr[i];
    }
  }
  f[0][0] = sum[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= i; ++j) {
      if (fl[i] == 1) {
        f[i][j] = sum[i - 1][j - 1];
      } else {
        f[i][j] = (sum[i - 1][j - 1] - sum[a[fl[i] - 1].first - 1][j - 1] + Mod) % Mod;
      }
      sum[i][j] = (sum[i - 1][j] + f[i][j]) % Mod;
    }
    sum[i][0] = sum[i - 1][0];
  }
  for (int i = 1; i <= n; ++i) {
    if (fr[i] == q) {
      for (int j = 1; j <= i; ++j) {
        g[j] = (g[j] + f[i][j]) % Mod;
      }
    }
  }
  for (int i = 1; i <= x; ++i) {
    for (int j = 1; j <= n; ++j) {
      p[i] = (p[i] + 1ll * g[j] * pw[i][j] % Mod * pw[x - i][n - j]) % Mod;
    }
  }
  int ans = 0;
  for (int i = 1; i <= x; ++i) {
    ans = (ans + 1ll * i * (p[i] - p[i - 1] + Mod)) % Mod;
  }
  ans = 1ll * ans * pow(pw[x][n], Mod - 2, Mod) % Mod;
  write(ans), EL;
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = 1ll * ans * now % m;
    }
    now = 1ll * now * now % m;
    b >>= 1;
  }
  return ans;
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
