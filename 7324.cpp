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

const int N = 50005;
const int M = 50005;
const int Mod = 1000000007;

void inc(int &a, int b) { (a += b) >= Mod ? a -= Mod : a; }
void dec(int &a, int b) { (a -= b) < 0 ? a += Mod : a; }

int build(int l, int r);
void dfs(int S, int u);

class Node {
 public:
  int x, l, r;
} tre[N];
int tot;

char ch[M];
int mat[M];
int a[11][N];
int dp[N][2];
int res[1 << 10];
int n, m;

int main() {
  read(n), read(m);
  for (int i = 0; i < m; ++i) {
    for (int j = 1; j <= n; ++j) {
      read(a[i][j]);
    }
  }
  scanf("%s", ch + 1);
  int len = strlen(ch + 1);
  int cnt = 0;
  {
    std::stack<int> S;
    for (int i = 1; i <= len; ++i) {
      if (ch[i] == '(') {
        S.push(i);
      } else if (ch[i] == ')') {
        mat[S.top()] = i;
        S.pop();
      } else if (ch[i] == '?') {
        ++cnt;
      }
    }
  }
  int rot = build(1, len);
  for (int i = 0; i < (1 << m); ++i) {
    dfs(i, rot);
    res[i] = dp[rot][1];
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    std::vector<int> V;
    for (int j = 0; j < m; ++j) {
      V.push_back(j);
    }
    std::sort(V.begin(), V.end(), [&](int x, int y) { return a[x][i] < a[y][i]; });
    int now = (1 << m) - 1, las = res[now];
    for (int j = 0; j < m; ++j) {
      now ^= (1 << V[j]);
      inc(ans, 1ll * (las - res[now] + Mod) % Mod * a[V[j]][i] % Mod);
      las = res[now];
    }
  }
  write(ans), EL;
  return 0;
}

int build(int l, int r) {
  bool fir = true;
  int now = 0;
  for (int i = l; i <= r; ++i) {
    if (ch[i] == '(') {
      if (fir) {
        fir = false;
        now = build(i + 1, mat[i] - 1);
      } else {
        tre[now].r = build(i + 1, mat[i] - 1);
      }
      i = mat[i];
    } else if (isNum(ch[i])) {
      if (fir) {
        fir = false;
        now = ++tot;
        tre[now].x = ch[i] - '0';
      } else {
        tre[now].r = ++tot;
        tre[tot].x = ch[i] - '0';
      }
    } else {
      tre[++tot].l = now;
      now = tot;
      if (ch[i] == '<') {
        tre[now].x = -1;
      } else if (ch[i] == '>') {
        tre[now].x = -2;
      } else {
        tre[now].x = -3;
      }
    }
  }
  return now;
}
void dfs(int S, int u) {
  dp[u][0] = 0, dp[u][1] = 0;
  if (tre[u].x >= 0) {
    dp[u][(S >> tre[u].x) & 1] = 1;
    return;
  }
  int l = tre[u].l, r = tre[u].r;
  dfs(S, l), dfs(S, r);
  if (tre[u].x != -1) {
    inc(dp[u][0], 1ll * dp[l][0] * dp[r][0] % Mod);
    inc(dp[u][1],
        (1ll * dp[l][0] * dp[r][1] + 1ll * dp[l][1] * dp[r][0] + 1ll * dp[l][1] * dp[r][1]) % Mod);
  }
  if (tre[u].x != -2) {
    inc(dp[u][0],
        (1ll * dp[l][0] * dp[r][0] + 1ll * dp[l][0] * dp[r][1] + 1ll * dp[l][1] * dp[r][0]) % Mod);
    inc(dp[u][1], 1ll * dp[l][1] * dp[r][1] % Mod);
  }
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
