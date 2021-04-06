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

constexpr int N = 11000005;

char tmp[N];
char ch[N << 1];
int t[N << 1];
int n;

int main() {
  scanf("%s", tmp + 1);
  n = strlen(tmp + 1);
  ch[0] = ch[1] = '#';
  for (int i = 1; i <= n; ++i) {
    ch[i << 1] = tmp[i];
    ch[i << 1 | 1] = '#';
  }
  int mid = 1, r = 0;
  for (int i = 1; i <= (n << 1 | 1); ++i) {
    if (i <= r) {
      t[i] = std::min(r - i, t[2 * mid - i]);
    }
    while (ch[i + t[i] + 1] == ch[i - t[i] - 1]) {
      ++t[i];
    }
    int tmp = i + t[i];
    if (tmp > r) {
      mid = i, r = tmp;
    }
  }
  int ans = 0;
  for (int i = 1; i <= (n << 1 | 1); ++i) {
    ans = std::max(ans, t[i]);
  }
  write(ans), EL;
  return 0;
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
