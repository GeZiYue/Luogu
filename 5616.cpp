#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T> void read(T &);
template <class T> void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

const int N = 305;
const int P = 70;
const int C = 300005;
#define GETALL                                                                 \
  for (a[1] = 0; a[1] <= 8; ++a[1])                                            \
    for (a[2] = 0; a[2] <= 5; ++a[2])                                          \
      for (a[3] = 0; a[3] <= 3; ++a[3])                                        \
        for (a[4] = 0; a[4] <= 2; ++a[4])                                      \
          for (a[5] = 0; a[5] <= 2; ++a[5])                                    \
            for (a[6] = 0; a[6] <= 2; ++a[6])                                  \
              for (a[7] = 0; a[7] <= 2; ++a[7])

void add(int &a, int b);
int pow(int a, int b, int m);
void work(int n);

bool isp[N];
int pri[N], id;
int dp[2][9][6][4][3][3][3][3];
int f[2][2][9][6][4][3][3][3][3];
int fac[N][8];
int a[8], b[8];
int cnt[N];
std::vector<int> V[N];
int pw2[C];
int n, Mod;

int main() {
  work(300);
  read(n), read(Mod);
  pw2[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw2[i] = pw2[i - 1] * 2 % Mod;
  }
  for (int i = 1; i <= n; ++i) {
    int a;
    read(a);
    ++cnt[a];
  }
  int cur = 1, las = 0;
  dp[0][0][0][0][0][0][0][0] = 1;
  for (int i = 1; i <= 300; ++i) {
    if (!cnt[i]) {
      continue;
    }
    int tmp = i;
    for (int j = 1; j <= 7; ++j) {
      while (tmp % pri[j] == 0) {
        tmp /= pri[j];
        ++fac[i][j];
      }
    }
    if (tmp > 1) {
      V[tmp].push_back(i);
      continue;
    }
    memcpy(dp[cur], dp[las], sizeof(dp[las]));
    int s = pw2[cnt[i]] - 1;
    GETALL {
      for (int j = 1; j <= 7; ++j) {
        b[j] = max(a[j], fac[i][j]);
      }
      add(dp[cur][b[1]][b[2]][b[3]][b[4]][b[5]][b[6]][b[7]],
          dp[las][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]] * 1ll * s % Mod);
    }
    cur ^= 1, las ^= 1;
  }
  GETALL {
    int now = 1;
    for (int j = 1; j <= 7; ++j) {
      now = (now * 1ll * pow(pri[j], a[j], Mod)) % Mod;
    }
    add(f[0][0][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]],
        dp[las][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]] * 1ll * now % Mod);
  }
  cur = 1, las = 0;
  for (int i = 1; i <= 300; ++i) {
    if (V[i].size()) {
      for (auto p : V[i]) {
        int now = pw2[cnt[p]] - 1;
        memcpy(f[cur], f[las], sizeof(f[las]));
        for (int st = 0; st <= 1; ++st) {
          GETALL {
            int tran = now;
            for (int j = 1; j <= 7; ++j) {
              b[j] = max(a[j], fac[p][j]);
              tran = tran * 1ll * pow(pri[j], b[j] - a[j], Mod) % Mod;
            }
            if (!st) {
              tran = tran * 1ll * i % Mod;
            }
            add(f[cur][1][b[1]][b[2]][b[3]][b[4]][b[5]][b[6]][b[7]],
                f[las][st][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]] * 1ll *
                    tran % Mod);
          }
        }
        cur ^= 1, las ^= 1;
      }
      GETALL {
        add(f[las][0][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]],
            f[las][1][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]]);
        f[las][1][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]] = 0;
      }
    }
  }
  int ans = 0;
  GETALL { add(ans, f[las][0][a[1]][a[2]][a[3]][a[4]][a[5]][a[6]][a[7]]); }
  write(ans), EL;
  return 0;
}

template <class T> inline void read(T &Re) {
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
template <class T> inline void write(const T &Wr) {
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

void add(int &a, int b) { ((a += b) >= Mod) ? (a -= Mod) : a; }
int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = ans * 1ll * now % m;
    }
    now = now * 1ll * now % m;
    b >>= 1;
  }
  return ans;
}
void work(int n) {
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
    }
    for (int j = 1; j <= id && i * pri[j] <= n; ++j) {
      isp[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        break;
      }
    }
  }
}
