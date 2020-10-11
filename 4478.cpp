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

const int N = 205;
const int Mod[] = {1000003, 3, 5, 6793, 10007};
const int MT = 1019663265;
const int mul[] = {0, MT / Mod[1], MT / Mod[2], MT / Mod[3], MT / Mod[4]};

int pow(int a, int b, int m);
int Lucas(int p, int n, int m);

std::vector<int> fac[5], ifac[5];
std::vector<pii> P;
std::vector<int> DP;
int n, m, t, p;

int main() {
  read(n), read(m), read(t), read(p);
  if (p == Mod[0]) {
    fac[0].reserve(Mod[0]);
    ifac[0].reserve(Mod[0]);
    fac[0].push_back(1);
    for (int i = 1; i < Mod[0]; ++i) {
      fac[0].push_back(fac[0][i - 1] * 1ll * i % Mod[0]);
    }
    ifac[0].push_back(pow(fac[0][Mod[0] - 1], Mod[0] - 2, Mod[0]));
    for (int i = Mod[0] - 1; i >= 1; --i) {
      ifac[0].push_back(ifac[0][Mod[0] - 1 - i] * 1ll * i % Mod[0]);
    }
    std::reverse(ifac[0].begin(), ifac[0].end());
  } else {
    for (int p = 1; p <= 4; ++p) {
      fac[p].reserve(Mod[p]);
      ifac[p].reserve(Mod[p]);
      fac[p].push_back(1);
      for (int i = 1; i < Mod[p]; ++i) {
        fac[p].push_back(fac[p][i - 1] * 1ll * i % Mod[p]);
      }
      ifac[p].push_back(pow(fac[p][Mod[p] - 1], Mod[p] - 2, Mod[p]));
      for (int i = Mod[p] - 1; i >= 1; --i) {
        ifac[p].push_back(ifac[p][Mod[p] - 1 - i] * 1ll * i % Mod[p]);
      }
      std::reverse(ifac[p].begin(), ifac[p].end());
    }
  }
  P.push_back(pii(0, 0));
  for (int i = 1; i <= t; ++i) {
    int x, y;
    read(x), read(y);
    P.push_back(pii(x, y));
  }
  P.push_back(pii(n, m));
  std::sort(P.begin(), P.end());
  DP.reserve(t + 2);
  DP.push_back(1);
  for (int i = 1; i <= t + 1; ++i) {
    DP.push_back(0);
  }
  std::vector<int> Ans;
  if (p == Mod[0]) {
    for (int i = 1; i <= t + 1; ++i) {
      for (int j = 0; j < i; ++j) {
        if (P[j].first <= P[i].first && P[j].second <= P[i].second) {
          DP[i] =
              (DP[i] -
               DP[j] * 1ll *
                   Lucas(0, P[i].first - P[j].first + P[i].second - P[j].second,
                         P[i].first - P[j].first) %
                   Mod[0] +
               Mod[0]) %
              Mod[0];
        }
      }
    }
    write((Mod[0] - DP[t + 1]) % Mod[0]), EL;
  } else {
    for (int p = 1; p <= 4; ++p) {
      DP[0] = 1;
      for (int i = 1; i <= t + 1; ++i) {
        DP[i] = 0;
      }
      for (int i = 1; i <= t + 1; ++i) {
        for (int j = 0; j < i; ++j) {
          if (P[j].first <= P[i].first && P[j].second <= P[i].second) {
            DP[i] =
                (DP[i] -
                 DP[j] * 1ll *
                     Lucas(p,
                           P[i].first - P[j].first + P[i].second - P[j].second,
                           P[i].first - P[j].first) %
                     Mod[p] +
                 Mod[p]) %
                Mod[p];
          }
        }
      }
      Ans.push_back((Mod[p] - DP[t + 1]) % Mod[p]);
    }
    int ans = 0;
    for (int p = 1; p <= 4; ++p) {
      ans = (ans + Ans[p - 1] * 1ll * mul[p] % MT *
                       pow(mul[p], Mod[p] - 2, Mod[p]) % MT) %
            MT;
    }
    write(ans), EL;
  }
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
int Lucas(int p, int n, int m) {
  if (m > n) {
    return 0;
  }
  if (m == 0) {
    return 1;
  }
  if (n < Mod[p] && m < Mod[p]) {
    return fac[p][n] * 1ll * ifac[p][m] % Mod[p] * ifac[p][n - m] % Mod[p];
  }
  return Lucas(p, n / Mod[p], m / Mod[p]) * 1ll *
         Lucas(p, n % Mod[p], m % Mod[p]) % Mod[p];
}
