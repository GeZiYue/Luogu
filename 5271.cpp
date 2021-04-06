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

const int N = 2005;

int p, k, n;

int main() {
  read(p), read(k);
  puts("YES");
  std::function<int(int, int)> plus = [](int a, int b) -> int {
    int ans = 0, pw = 1;
    for (int i = 0; i < k; ++i, a /= p, b /= p, pw *= p) ans += (a % p + b % p + p) % p * pw;
    return ans;
  };
  int n = 1;
  for (int i = 0; i < k; ++i) n *= p;
  std::vector<std::vector<bool>> ok(n, std::vector<bool>(n));
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (!ok[i][j]) {
        std::vector<int> now;
        now.push_back(i);
        int v = plus(j, -i);
        for (int l = 1; l < p; ++l) now.push_back(plus(now.back(), v));
        for (int i : now) {
          write(i), SP;
          for (int j : now) ok[i][j] = true;
        }
        EL;
      }
    }
  }
  return 0;
}

template <typename T>
void read(T &Re) {
  T k = 0;
  char ch = getchar();
  int flag = 1;
  while (!isNum(ch)) {
    if (ch == '-') flag = -1;
    ch = getchar();
  }
  while (isNum(ch)) {
    k = (k << 1) + (k << 3) + ch - '0';
    ch = getchar();
  }
  Re = flag * k;
}
template <typename T>
void write(const T &Wr) {
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
