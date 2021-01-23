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

constexpr int N = 1005;

int query(int x, int y);
int solve(int n, bool op);

int a[N];
int ans[N];
int hg[N];
int n;

int main() {
  read(n);
  hg[1] = 1;
  for (int i = 2; i <= n; ++i) {
    hg[i] = hg[i >> 1] << 1;
  }
  for (int i = 1; i <= n; ++i) {
    ans[i] = solve(i, 0);
  }
  putchar('!'), SP;
  for (int i = 1; i <= n; ++i) {
    write(ans[i]), SP;
  }
  EL;
  return 0;
}

int query(int x, int y) {
  int ans;
  putchar('?'), SP, write(x), SP, write(y), EL, fflush(stdout), read(ans);
  return ans;
}
int solve(int n, bool op) {
  if (n == 1) {
    return a[1] = query(1, 1);
  }
  int ans = 0;
  if (!op) {
    for (int i = 1; i < n; ++i) {
      if (a[i] == i) {
        continue;
      }
      bool x = query(n, i);
      if (x) {
        ans += i - a[i], a[i] = i;
      } else {
        int tmp = a[i];
        return ans + solve(i, 1) - tmp;
      }
    }
    return ans + solve(n, 1);
  } else {
    for (int i = hg[n - 1]; i; i >>= 1) {
      int x = query(i, n);
      if (x) {
        a[n] = n;
        return n - ans - (i - solve(i, 1));
      } else {
        ans += i;
        a[i] = 0;
      }
    }
    a[n] = ans;
    return 0;
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
