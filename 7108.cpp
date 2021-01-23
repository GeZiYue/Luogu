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

constexpr int Mod = 1000000007;

int pow(int a, int b, int m);

int main() {
  int T;
  read(T);
  while (T--) {
    int a, b, h;
    read(a), read(b), read(h);
    if (h == 0) {
      write(a), EL;
      continue;
    }
    int bh = pow(b, h, Mod);
    if (a == b) {
      write(1ll * a * bh % Mod), EL;
      continue;
    }
    if (a >= b) {
      if (b == 1) {
        write((1ll * a * bh + 1ll * (a - b) * h) % Mod), EL;
        continue;
      }
      int ans = (1ll * a * bh + 1ll * (a - b) * (bh - 1) % Mod * pow(b - 1, Mod - 2, Mod)) % Mod;
      write(ans), EL;
    } else {
      int ans = 1ll * bh * a % Mod;
      write(ans), EL;
    }
  }
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
