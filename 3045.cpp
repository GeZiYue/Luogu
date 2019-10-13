#include <unordered_set>
#include <unordered_map>
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
inline void read(T&);
template<class T>
inline void write(const T&);

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
const int N = 50005;

class Node {
public:
  int p, c;
}a[N];

bool cmp(const Node &i, const Node &j) {
  return i.c < j.c;
}
bool cmp2(const Node &i, const Node &j) {
  return i.p < j.p;
} 

std::priority_queue<int, std::vector<int>, std::greater<int> > pq;

int main () {
  int n, m;
  int ans = 0;
  ll k, now = 0;
  read(n), read(m), read(k);
  for (int i = 1; i <= n; ++i) {
    read(a[i].p), read(a[i].c);
  }
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1; i <= m; ++i) {
    now += a[i].c;
    pq.push(a[i].p - a[i].c);
    if (now >= k) {
      write(ans), EL;
      return 0;
    } else {
      ++ans;
    }
  }
  sort(a + m + 1, a + n + 1, cmp2);
  for (int i = m + 1; i <= n; ++i) {
    if (a[i].p - a[i].c > pq.top()) {
      if (now + a[i].c + pq.top() <= k) {
        now += a[i].c + pq.top();
        pq.pop();
        pq.push(a[i].p - a[i].c);
        ++ans;
      }
    } else {
      if (now + a[i].p <= k) {
        now += a[i].p;
        ++ans;
      }
    }
  }
  write(ans), EL;
  return 0;
}

template<class T>
void read(T &Re) {
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
