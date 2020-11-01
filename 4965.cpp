#include <algorithm>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar(' ')
#define EL putchar('\n')
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
void read(T &);
template <class T>
void write(const T &);

typedef long long ll;
typedef unsigned long long ull;
typedef const long long &cll;
typedef const int &ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::abs;
using std::max;
using std::min;

const int N = 5000005;
const int M = 30;
const int Mod = 19260817;

char A[N], B[N];
int S[M];
int n, m;

int main() {
  read(n), read(m);
  scanf("%s", A + 1);
  scanf("%s", B + 1);
  int ans = 1, cnt = n;
  for (int i = 1; i <= m; ++i) {
    if (B[i] == 'u') {
      if (!cnt) {
        continue;
      }
      ans = (ans + 1) % Mod;
      S[A[cnt] - 'A'] = (S[A[cnt] - 'A'] + 1) % Mod;
      --cnt;
    } else {
      int tmp = S[B[i] - 'A'];
      S[B[i] - 'A'] = ans;
      ans = (ans * 2ll - tmp + Mod) % Mod;
    }
  }
  write(ans), EL;
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
