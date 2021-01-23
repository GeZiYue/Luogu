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

constexpr int N = 7105;

ll dp[N][N];
int a[N];
int que[N], qh, qt;
int n;

int main() {
  int T;
  read(T);
  while (T--) {
    read(n);
    for (int i = 1; i <= n; ++i) {
      read(a[i]);
    }
    for (int r = 2; r <= n; ++r) {
      int now = r;
      dp[r - 1][r] = a[r - 1];
      que[qh = qt = 1] = r - 1;
      for (int l = r - 2; l >= 1; --l) {
        while (dp[l][now - 1] > dp[now][r]) {
          --now;
        }
        dp[l][r] = dp[l][now] + a[now];
        while (qh <= qt && que[qh] >= now) {
          ++qh;
        }
        dp[l][r] = std::min(dp[l][r], dp[que[qh] + 1][r] + a[que[qh]]);
        while (qh <= qt && dp[l + 1][r] + a[l] <= dp[que[qt] + 1][r] + a[que[qt]]) {
          --qt;
        }
        que[++qt] = l;
      }
    }
    write(dp[1][n]), EL;
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
