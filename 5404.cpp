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

const int N = 2005;
const int Mod = 998244353;

char s[N];
int nxt[N], max[N];
int ch[N][26];
int f[N][N];
int n, m;

int main() {
  read(m);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  nxt[0] = -1;
  for (int i = 1, j = -1; i <= n; ++i) {
    while (~j && s[j + 1] != s[i]) j = nxt[j];
    nxt[i] = ++j;
  }
  for (int i = 0; i <= n; ++i) {
    for (int c = 0; c < 26; ++c) {
      if (s[i + 1] - 'a' == c)
        ch[i][c] = i + 1;
      else 
        ch[i][c] = (i ? ch[nxt[i]][c] : 0);
      if (ch[i][c]) max[i] = c;
    }
  }
  f[0][0] = 1;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= n; ++j) {
      for (int c = max[j]; c < 26; ++c) {
        f[i + 1][ch[j][c]] = (f[i + 1][ch[j][c]] + f[i][j]) % Mod;
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    int u = i;
    for (int j = 1; j <= m; ++j) {
      ans = (ans + 1ll * (26 - max[u] - 1) * f[m - j][i]) % Mod;
      u = ch[u][max[u]];
      if (!u) break;
    }
    ans += (u && u == i);
  }
  int pw = 1;
  for (int i = 1; i <= m; ++i) pw = 1ll * pw * 26 % Mod;
  write((pw - ans + Mod) % Mod), EL;
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

