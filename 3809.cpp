#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <complex>
#include <cstdio>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <map>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template<class T>
void read(T&);
template<class T>
void write(const T&);

typedef long long ll;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 1000005;

char ch[N];
int cnt[N], sa[N], rk[N];
int tmp[N << 1], id[N];
int n, m = 130, p;

int main () {
  scanf("%s", ch + 1);
  n = strlen(ch + 1);
  for (int i = 1; i <= n; ++i) {
    ++cnt[rk[i] = ch[i]];
  }
  for (int i = 1; i <= m; ++i) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = n; i >= 1; --i) {
    sa[cnt[rk[i]]--] = i;
  }
  for (int w = 1; w <= n; w <<= 1, m = p) {
    p = 0;
    for (int i = n - w + 1; i <= n; ++i) {
      id[++p] = i;
    }
    for (int i = 1; i <= n; ++i) {
      if (sa[i] > w) {
        id[++p] = sa[i] - w;
      }
    }
    for (int i = 1; i <= m; ++i) {
      cnt[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
      ++cnt[rk[id[i]]];
    }
    for (int i = 1; i <= m; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n; i >= 1; --i) {
      sa[cnt[rk[id[i]]]--] = id[i];
    }
    for (int i = 1; i <= n; ++i) {
      tmp[i] = rk[i];
    }
    p = 0;
    for (int i = 1; i <= n; ++i) {
      rk[sa[i]] = ((tmp[sa[i]] == tmp[sa[i - 1]] && tmp[sa[i] + w] == tmp[sa[i - 1] + w]) ? p : ++p);
    }
  }
  for (int i = 1; i <= n; ++i) {
    write(sa[i]), SP;
  }
  EL;
  return 0;
}

template<class T>
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
template<class T>
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
