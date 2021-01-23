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

const int N = 2000005;

int pre[N], suf[N];
int cnt[30], now;
char ch[N];
int nxt[N];
int T, n;

int main() {
  read(T);
  while (T--) {
    memset(pre, 0, sizeof(pre));
    memset(suf, 0, sizeof(suf));
    memset(cnt, 0, sizeof(cnt));
    now = 0;
    scanf("%s", ch + 1);
    n = strlen(ch + 1);
    for (int i = 1; i <= n; ++i) {
      ++cnt[ch[i] - 'a'];
      if (cnt[ch[i] - 'a'] & 1) {
        ++now;
      } else {
        --now;
      }
      pre[i] = now;
    }
    memset(cnt, 0, sizeof(cnt));
    now = 0;
    for (int i = n; i >= 1; --i) {
      ++cnt[ch[i] - 'a'];
      if (cnt[ch[i] - 'a'] & 1) {
        ++now;
      } else {
        --now;
      }
      suf[i] = now;
    }
    memset(cnt, 0, sizeof(cnt));
    memset(nxt, 0, sizeof(nxt));
    for (int i = 2, j = 0; i <= n; ++i) {
      while (j && ch[j + 1] != ch[i]) {
        j = nxt[j];
      }
      if (ch[j + 1] == ch[i]) {
        ++j;
      }
      nxt[i] = j;
    }
    ll ans = 0;
    for (int i = 2; i < n; ++i) {
      for (int j = pre[i - 1]; j <= 26; ++j) {
        ++cnt[j];
      }
      for (int j = i; j < n; j += i) {
        int tmp = j - nxt[j];
        if (i % tmp != 0 && j != i) {
          break;
        }
        ans += cnt[suf[j + 1]];
      }
    }
    write(ans), EL;
  }
  return 0;
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
