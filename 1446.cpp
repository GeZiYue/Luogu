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

const int N = 25;
const int M = 65;

void inc(int &a, int b);
int pow(int a, int b, int m);
int calc();

int X[M];
bool vis[M];
int dp[N][N][N];
int sr, sg, sb;
int n, m, P;

int main() {
  read(sr), read(sg), read(sb), read(m), read(P);
  n = sr + sg + sb;
  bool hase = false;
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    bool ise = true;
    for (int j = 1; j <= n; ++j) {
      read(X[j]);
      ise &= (X[j] == j);
    }
    hase |= ise;
    inc(ans, calc());
  }
  if (!hase) {
    ++m;
    for (int j = 1; j <= n; ++j) {
      X[j] = j;
    }
    inc(ans, calc());
  }
  write(1ll * ans * pow(m, P - 2, P) % P), EL;
  return 0;
}

int calc() {
  std::vector<int> Cyc;
  memset(vis, 0, sizeof(vis));
  memset(dp, 0, sizeof(dp));
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) {
      int now = 0;
      for (int j = i; !vis[j]; j = X[j]) vis[j] = true, ++now;
      Cyc.push_back(now);
    }
  }
  dp[0][0][0] = 1;
  for (int c : Cyc) {
    for (int i = sr; i >= 0; --i) {
      for (int j = sg; j >= 0; --j) {
        for (int k = sb; k >= 0; --k) {
          if (i >= c) inc(dp[i][j][k], dp[i - c][j][k]);
          if (j >= c) inc(dp[i][j][k], dp[i][j - c][k]);
          if (k >= c) inc(dp[i][j][k], dp[i][j][k - c]);
        }
      }
    }
  }
  return dp[sr][sg][sb];
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) ans = 1ll * ans * now % m;
    now = 1ll * now * now % m;
    b >>= 1;
  }
  return ans;
}
void inc(int &a, int b) { (a += b) >= P ? a -= P : a; }

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
