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

constexpr int N = 20;
constexpr int M = 1 << 19;
constexpr int Mod = 998244353, iv2 = (Mod + 1) / 2;

class SPS {
 public:
  int a[M][N];
  int s;
  void FWT(bool opt);
  void inv(SPS &ans);
};

int pow(int a, int b, int m);

int popc[M];
bool f[N][N];
int n, m, S;

int main() {
  read(n), read(m);
  S = 1 << n;
  for (int i = 1; i < S; ++i) {
    popc[i] = popc[i >> 1] + (i & 1);
  }
  for (int i = 1; i <= m; ++i) {
    int u, v;
    read(u), read(v);
    f[u - 1][v - 1] = f[v - 1][u - 1] = true;
  }
  SPS F, G;
  for (int i = 0; i < S; ++i) {
    bool flag = true;
    for (int j = 0; j < n; ++j) {
      if ((i >> j) & 1) {
        for (int k = 0; k < n; ++k) {
          if ((i >> k) & 1) {
            if (f[j][k]) {
              flag = false;
              break;
            }
          }
        }
        if (!flag) {
          break;
        }
      }
    }
    if (flag) {
      G.a[i][popc[i]] = (popc[i] & 1) ? Mod - 1 : 1;
    }
  }
  G.s = n;
  G.inv(F);
  write(1ll * F.a[S - 1][n] * m % Mod * iv2 % Mod), EL;
  return 0;
}

void SPS::FWT(bool opt) {
  for (int l = 1; l < 1 << s; l <<= 1) {
    for (int i = 0; i < 1 << s; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        for (int k = 0; k <= s; ++k) {
          int x = a[i | j][k], y = a[i | j | l][k];
          a[i | j][k] = (x + y) % Mod;
          a[i | j | l][k] = (x - y + Mod) % Mod;
        }
      }
    }
  }
  if (opt) {
    int iv = pow(1 << s, Mod - 2, Mod);
    for (int i = 0; i < 1 << s; ++i) {
      for (int j = 0; j <= s; ++j) {
        a[i][j] = 1ll * a[i][j] * iv % Mod;
      }
    }
  }
}
void SPS::inv(SPS &ans) {
  FWT(false);
  for (int i = 0; i < 1 << s; ++i) {
    ans.a[i][0] = pow(a[i][0], Mod - 2, Mod);
    for (int j = 1; j <= s; ++j) {
      for (int k = 0; k < j; ++k) {
        ans.a[i][j] = (ans.a[i][j] + 1ll * ans.a[i][k] * a[i][j - k]) % Mod;
      }
      ans.a[i][j] = 1ll * (Mod - ans.a[i][j]) * pow(a[i][0], Mod - 2, Mod) % Mod;
    }
  }
  ans.s = s;
  ans.FWT(true);
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
