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

constexpr int N = 10000000;

int pow(int a, int b, int m);
void pre(int n);
int f1(ll n);
int f2(ll n);
int f3(ll n);
int S(ll n);
int W(ll n);

bool isp[N + 5];
int phi[N + 5];
int sum[N + 5];
int pri[N], id;
std::unordered_map<ll, int> mp;
int iv6;
int Mod;
ll n;

int main() {
  read(Mod), read(n);
  iv6 = pow(6, Mod - 2, Mod);
  pre(std::min(n, N * 1ll));
  write(W(n)), EL;
  return 0;
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
void pre(int n) {
  phi[1] = 1;
  sum[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!isp[i]) {
      pri[++id] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= id && i * pri[j] <= n; ++j) {
      isp[i * pri[j]] = true;
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j];
        break;
      }
      phi[i * pri[j]] = phi[i] * (pri[j] - 1);
    }
    sum[i] = (sum[i - 1] + 1ll * phi[i] * i % Mod * i % Mod) % Mod;
  }
}
int f1(ll n) { return n %= Mod, n * (n + 1) / 2 % Mod; }
int f2(ll n) { return n %= Mod, n * (n + 1) % Mod * (2 * n + 1) % Mod * iv6 % Mod; }
int f3(ll n) { return 1ll * f1(n) * f1(n) % Mod; }
int S(ll n) {
  if (n <= N) {
    return sum[n];
  }
  if (mp.count(n)) {
    return mp[n];
  }
  int ans = f3(n);
  for (ll l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ans = (ans - 1ll * S(n / l) * (f2(r) - f2(l - 1) + Mod) % Mod + Mod) % Mod;
  }
  return mp[n] = ans;
}
int W(ll n) {
  int ans = 0;
  int las = 0;
  for (ll l = 1, r; l <= n; l = r + 1) {
    r = n / (n / l);
    int now = S(r);
    ans = (ans + 1ll * f3(n / l) * (now - las + Mod) % Mod) % Mod;
    las = now;
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
