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

constexpr int N = 40;
constexpr int M = 1 << 20;
constexpr int Mod = 1000000007;

class Poly {
 public:
  int *a, deg;
  Poly() {
    a = new int[N];
    memset(a, 0, sizeof(int) * N);
    deg = 0;
  }
  void init(int v);
  Poly inv();
};

int pow(int a, int b, int m);
void dfs(int x);
int NFC(int n, int v);
int calc(const Poly &F);

int nxt[N];
int a[N];
bool ok[M];
int f[M];
int n, m, S;

int main() {
  read(n), read(m);
  int ans = 0;
  for (S = 1; S <= n; ++S) {
    int lim = 1 << S;
    memset(f, 0, sizeof(f));
    memset(ok, false, sizeof(ok));
    dfs(1);
    for (int i = lim - 1; i; --i) {
      if (!ok[i]) {
        continue;
      }
      f[i] = pow(m, NFC(S, i), Mod);
      for (int j = (i + 1) | i; j < lim; j = (j + 1) | i) {
        f[i] = (f[i] - f[j] + Mod) % Mod;
      }
      Poly F;
      F.init(i);
      ans = (ans + 1ll * f[i] * calc(F)) % Mod;
    }
  }
  write(1ll * ans * pow(m, 1ll * n * (Mod - 2) % (Mod - 1), Mod) % Mod), EL;
  return 0;
}

void Poly::init(int v) {
  for (int i = 0; i < S; ++i) {
    if ((v >> i) & 1) {
      a[i] = 1;
    }
  }
}
Poly Poly::inv() {
  Poly ans;
  ans.a[0] = pow(a[0], Mod - 2, Mod);
  ans.deg = deg;
  for (int i = 1; i <= deg; ++i) {
    for (int j = 0; j < i; ++j) {
      ans.a[i] = (ans.a[i] - 1ll * ans.a[j] * a[i - j] % Mod + Mod) % Mod;
    }
    ans.a[i] = 1ll * ans.a[i] * pow(a[0], Mod - 2, Mod) % Mod;
  }
  return ans;
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
void dfs(int x) {
  if (x == S + 1) {
    int v = 0, now = S;
    while (now) {
      v |= (1 << (S - now));
      now = nxt[now];
    }
    ok[v] = true;
    return;
  }
  for (int &c = a[x] = 0; c <= 1; ++c) {
    int j = nxt[x - 1];
    while (j && a[j + 1] != c) {
      j = nxt[j];
    }
    if (x != 1 && a[j + 1] == c) {
      ++j;
    }
    nxt[x] = j;
    dfs(x + 1);
  }
}
int NFC(int n, int v) {
  int l = 0, ans = 0;
  while (true) {
    int i = 1;
    while (i < n && !((v >> (l + i)) & 1)) {
      ++i;
    }
    if (i == n) {
      return n + ans;
    }
    if (i == 1) {
      return 1 + ans;
    }
    if (i * 2 <= n) {
      l += n - i - n % i;
      n = i + n % i;
    } else {
      ans += i * 2 - n;
      l += i;
      n -= i;
    }
  }
}
int calc(const Poly &F) {
  Poly G;
  G.a[0] = 1, G.a[1] = 2 * (Mod - m) % Mod, G.a[2] = 1ll * m * m % Mod;
  Poly ans;
  for (int i = 0; i < S; ++i) {
    for (int j = 0; j <= 2; ++j) {
      ans.a[i + j] = (ans.a[i + j] + 1ll * F.a[i] * G.a[j]) % Mod;
    }
  }
  ++ans.a[S];
  ans.a[S + 1] = (ans.a[S + 1] - m + Mod) % Mod;
  ans.deg = n;
  ans = ans.inv();
  return ans.a[n - S];
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
