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

constexpr int N = 1000005;
constexpr int Mod = 998244353;

int pow(int a, int b, int m);

int fac[N], ifac[N];
char ch[N];
int n;

int main() {
  read(n);
  n <<= 1;
  scanf("%s", ch + 1);
  int num = 0;
  fac[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fac[i] = 1ll * fac[i - 1] * i % Mod;
  }
  ifac[n] = pow(fac[n], Mod - 2, Mod);
  for (int i = n - 1; i >= 0; --i) {
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % Mod;
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    num += (ch[i] == '(' ? 1 : -1);
    if (num == 0) {
      ++ans;
    }
  }
  write(1ll * pow(2, ans, Mod) * fac[n / 2] % Mod * fac[n / 2] % Mod * ifac[n] % Mod), EL;
  return 0;
}

int pow(int a, int b, int m) {
  int ans = 1, now = a;
  while (b) {
    if (b & 1) {
      ans = 1ll * now * ans % m;
    }
    now = 1ll * now * now % m;
    b >>= 1;
  }
  return ans;
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
