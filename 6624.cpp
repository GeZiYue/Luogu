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

constexpr int N = 35;
constexpr int M = N * N;
constexpr int K = 200000;
constexpr int Mod = 998244353;

int pow(int a, int b, int m);

class Poly {
 public:
  int a, b;
  friend Poly operator+(Poly a, Poly b) { return {(a.a + b.a) % Mod, (a.b + b.b) % Mod}; }
  friend Poly operator-(Poly a, Poly b) {
    return {(a.a - b.a + Mod) % Mod, (a.b - b.b + Mod) % Mod};
  }
  friend Poly operator*(Poly a, Poly b) {
    return {static_cast<int>(1ll * a.a * b.a % Mod),
            static_cast<int>((1ll * a.a * b.b + 1ll * a.b * b.a) % Mod)};
  }
  Poly inv() {
    int iv = pow(a, Mod - 2, Mod);
    return {iv, static_cast<int>(Mod - 1ll * b * iv % Mod * iv % Mod)};
  }
  friend Poly operator/(Poly a, Poly b) {
    if (b.a) {
      return a * b.inv();
    } else {
      return {static_cast<int>(1ll * a.b * pow(b.b, Mod - 2, Mod) % Mod), 0};
    }
  }
  int lw() { return a ? 0 : (b ? 1 : 2); }
};

int det();

Poly f[N][N];
int u[M], v[M], w[M];
int phi[K], pri[K], id;
bool isp[K];
int n, m;

int main() {
  read(n), read(m);
  int ans = 0;
  for (int i = 1; i <= m; ++i) {
    read(u[i]), read(v[i]), read(w[i]);
    f[u[i]][u[i]] = f[u[i]][u[i]] + Poly{1, w[i]};
    f[v[i]][v[i]] = f[v[i]][v[i]] + Poly{1, w[i]};
    f[u[i]][v[i]] = f[u[i]][v[i]] - Poly{1, w[i]};
    f[v[i]][u[i]] = f[v[i]][u[i]] - Poly{1, w[i]};
  }
  ans = det();
  phi[1] = 1;
  for (int i = 2; i <= 152501; ++i) {
    if (!isp[i]) {
      phi[i] = i - 1;
      pri[++id] = i;
    }
    for (int j = 1; j <= id && i * pri[j] <= 152501; ++j) {
      isp[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
      phi[i * pri[j]] = phi[i] * (pri[j] - 1);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        f[i][j] = Poly{0, 0};
      }
    }
    int num = 0;
    for (int j = 1; j <= m; ++j) {
      if (w[j] % i == 0) {
        ++num;
        f[u[j]][u[j]] = f[u[j]][u[j]] + Poly{1, w[j]};
        f[v[j]][v[j]] = f[v[j]][v[j]] + Poly{1, w[j]};
        f[u[j]][v[j]] = f[u[j]][v[j]] - Poly{1, w[j]};
        f[v[j]][u[j]] = f[v[j]][u[j]] - Poly{1, w[j]};
      }
    }
    if (num >= n - 1) {
      ans = (ans + 1ll * det() * phi[i]) % Mod;
    }
  }
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
int det() {
  Poly ans{1, 0};
  for (int i = 1; i < n; ++i) {
    int tmp = i;
    for (int j = i; j < n; ++j) {
      if (f[j][i].lw() < f[tmp][i].lw()) {
        tmp = j;
        break;
      }
    }
    if (f[tmp][i].lw() == 2) {
      return 0;
    }
    if (i != tmp) {
      ans.a = Mod - ans.a, ans.b = Mod - ans.b;
      std::swap(f[i], f[tmp]);
    }
    ans = ans * f[i][i];
    for (int j = i + 1; j < n; ++j) {
      Poly tmp = f[j][i] / f[i][i];
      for (int k = i; k < n; ++k) {
        f[j][k] = f[j][k] - f[i][k] * tmp;
      }
    }
  }
  return ans.b;
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
