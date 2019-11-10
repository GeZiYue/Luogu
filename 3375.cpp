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

char s1[N], s2[N];
int pi[N];

int main () {
  scanf("%s\n%s", s2, s1);
  int n = strlen(s1), m = strlen(s2);
  for (int i = 1; i < n; ++i) {
    int j = pi[i - 1];
    while (j && s1[j] != s1[i]) {
      j = pi[j - 1];
    }
    if (s1[j] == s1[i]) {
      ++j;
    }
    pi[i] = j;
  }
  for (int i = 0, j = 0; i < m; ++i) {
    while (j && s1[j] != s2[i]) {
      j = pi[j - 1];
    }
    if (s1[j] == s2[i]) {
      ++j;
    }
    if (j == n) {
      write(i - n + 2), EL;
    }
  }
  for (int i = 0; i < n; ++i) {
    write(pi[i]), SP;
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
