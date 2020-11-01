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

template <class T>
void read(T &);
template <class T>
void write(const T &);

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

const int N = 50000;
const int B = 200;
const int Mod = 23333;

void work(int n);

bool isp[N + 1];
int pri[N + 1], phi[N + 1], mu[N + 1], id;
std::vector<int> G[N + 1];
std::vector<int> F[B + 1][B + 1];
int T, n, m;

int main() {
  work(N);
  G[0].resize(N);
  for (int i = 1; i <= N; ++i) {
    G[i].resize(N / i + 1);
    for (int j = 1; j <= N / i; ++j) {
      G[i][j] = (G[i - 1][j] + phi[i * j]) % Mod;
    }
  }
  for (int i = 1; i <= B; ++i) {
    for (int j = i; j <= B; ++j) {
      int lim = N / j;
      F[i][j].resize(lim + 1);
      for (int k = 1; k <= lim; ++k) {
        int tmp = mu[k] * G[i][k] % Mod * G[j][k] % Mod;
        for (int t = k; t <= lim; t += k) {
          F[i][j][t] = (F[i][j][t] + tmp) % Mod;
        }
      }
      for (int k = 1; k <= lim; ++k) {
        (F[i][j][k] += F[i][j][k - 1]) %= Mod;
      }
    }
  }
  read(T);
  while (T--) {
    read(n), read(m);
    if (m > n) {
      std::swap(n, m);
    }
    int sum = 0;
    for (int i = 1; i <= n / B; ++i) {
      for (int j = i; j <= n / B; j += i) {
        sum = (sum + mu[i] * G[n / j][i] % Mod * G[m / j][i] % Mod) % Mod;
      }
    }
    int l = n / B + 1, r;
    for (; l <= m; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      int tn = n / l, tm = m / l;
      sum = (sum + F[tm][tn][r] - F[tm][tn][l - 1] + Mod) % Mod;
    }
    write((sum + Mod) % Mod), EL;
  }
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

void work(int n) {
  mu[1] = phi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
      phi[i] = i - 1;
      mu[i] = Mod - 1;
    }
    for (int j = 1; j <= id && i * pri[j] <= n; ++j) {
      isp[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        mu[i * pri[j]] = 0;
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
      mu[i * pri[j]] = Mod - mu[i];
      phi[i * pri[j]] = phi[i] * (pri[j] - 1);
    }
  }
}
