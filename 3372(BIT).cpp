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
const int N = 100005;
#define lowbit(x) (x & (-x))

void update(int, int, ll);
ll query(int, int);

ll BIT1[N], BIT2[N];
int n;

int main () {
  int m;
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    int a;
    read(a);
    update(i, i, a);
  }
  for (int i = 1; i <= m; ++i) {
    int type, l, r;
    read(type), read(l), read(r);
    if (type == 1) {
      ll k;
      read(k);
      update(l, r, k);
    } else {
      write(query(l, r)), EL;
    }
  }
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


inline ll query1(int x) {
  ll ans = 0;
  while (x) {
    ans += BIT1[x];
    x -= lowbit(x);
  }
  return ans;
}
inline ll query2(int x) {
  ll ans = 0;
  while (x) {
    ans += BIT2[x];
    x -= lowbit(x);
  }
  return ans;
}
inline void update1(int x, ll num) {
  while (x <= n) {
    BIT1[x] += num;
    x += lowbit(x);
  }
}
inline void update2(int x, ll num) {
  while (x <= n) {
    BIT2[x] += num;
    x += lowbit(x);
  }
}
inline void update(int l, int r, ll num) {
  update1(l, num), update1(r + 1, -num);
  update2(l, num * l), update2(r + 1, -num * (r + 1));
}
inline ll query(int l, int r) {
  return ((r + 1) * query1(r) - query2(r)) - ((l) * query1(l - 1) - query2(l - 1));
}

/*
b_i = a_i - a_{i-1}
c_i = b_i * i
a_1 + a_2 _ ... + a_i
= b_1 + (b_1 + b_2) + ... +(b_1 + b_2 + b_3 + ... + b_i)
= i * b_1 + (i - 1) * b_2 + ... + b_i
= (i + 1) * (b_1 + b_2 + b_3 + ... b_i) - (c_1 + c_2 + c_3 + ... + c_i)
*/
