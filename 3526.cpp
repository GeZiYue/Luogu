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

void solve(int l, int r);

char ch[N];
int ans[N];
int nxt[N];
int n;

int main() {
  int T;
  read(T);
  while (T--) {
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    solve(1, n);
    for (int i = 1; i <= n; ++i) {
      write(ans[i]);
    }
    EL;
  }
  return 0;
}

void solve(int l, int r) {
  int len = r - l + 1;
  bool flag = true;
  for (int i = l + 1; i <= r; ++i) {
    if (ch[i] != ch[i - 1]) {
      flag = false;
    }
  }
  if (flag) {
    for (int i = l; i <= r; ++i) {
      ans[i] = 0;
    }
    return;
  }
  for (int i = 2, j = 0; i <= len; ++i) {
    while (j && ch[i + l - 1] != ch[j + l]) {
      j = nxt[j];
    }
    if (ch[i + l - 1] == ch[j + l]) {
      ++j;
    }
    nxt[i] = j;
  }
  int s = nxt[len], v = len - nxt[len];
  if (!s) {
    for (int i = l; i < r; ++i) {
      ans[i] = 0;
    }
    ans[r] = 1;
    return;
  }
  if (2 * v <= len) {
    int L = v + len % v;
    solve(r - L + 1, r);
    for (int i = r - L; i >= l; --i) {
      ans[i] = ans[i + v];
    }
  } else {
    solve(l, l + s - 1);
    for (int i = l; i < l + s; ++i) {
      ans[i + v] = ans[i];
    }
    for (int i = l + s; i <= r - s; ++i) {
      ans[i] = 0;
    }
    for (int i = 2, j = 0; i <= len; ++i) {
      while (j && ans[i + l - 1] != ans[j + l]) {
        j = nxt[j];
      }
      if (ans[i + l - 1] == ans[j + l]) {
        ++j;
      }
      nxt[i] = j;
    }
    if (nxt[len] != s) {
      ans[r - s] = 1;
    }
  }
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
