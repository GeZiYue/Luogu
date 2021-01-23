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

constexpr int N = 200005;

int gcd(int a, int b);

int a[N], tot;
int b[N];
ll f[N];
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    read(a[i]);
  }
  for (int i = 0; i <= n; ++i) {
    f[i] = -1;
  }
  std::sort(a + 1, a + n + 1, std::greater<int>());
  while (m--) {
    int k;
    read(k);
    int t = n / gcd(k, n);
    if (f[t] != -1) {
      write(f[t]), EL;
      continue;
    }
    for (int i = 1; i <= n; ++i) {
      b[i] = 0;
    }
    tot = 0;
    for (int i = 1; i <= n; ++i) {
      if (!b[i]) {
        b[i] = a[++tot];
        int l = i + k, r = i - k;
        if (l > n) {
          l -= n;
        }
        if (r <= 0) {
          r += n;
        }
        if (l == r) {
          if (!b[l]) {
            b[l] = a[++tot];
          }
        } else {
          while (!b[l] && !b[r]) {
            if (l == r) {
              b[l] = a[++tot];
              break;
            }
            b[l] = a[++tot];
            b[r] = a[++tot];
            l += k;
            if (l > n) {
              l -= n;
            }
            r -= k;
            if (r <= 0) {
              r += n;
            }
          }
        }
      }
    }
    ll ans = 0;
    for (int i = 1; i <= k; ++i) {
      ans += b[i] * 1ll * b[n + i - k];
    }
    for (int i = 1; i <= (n - k); ++i) {
      ans += b[i] * 1ll * b[i + k];
    }
    write(f[t] = ans), EL;
  }
  return 0;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

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
