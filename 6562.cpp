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

constexpr int N = 1 << 16 | 5;
constexpr int M = 200005;

void FWT_and(uint *A, int lim);
void FWT_or(uint *A, int lim);
uint query(int x, int y);
void update(int x, int y, uint k);
void rebuild();

int stax[M], stay[M], top;
uint stak[M];
uint val[N], sum[N], tagv[N], tags[N];
int popc[N];
int half;
int n, q;

int main() {
  read(n), read(q);
  half = n >> 1;
  n = 1 << n;
  for (int i = 0; i < n; ++i) {
    read(val[i]);
    sum[i] = val[i];
    popc[i] = popc[i >> 1] + (i & 1);
  }
  FWT_or(sum, n);
  int B = 3500;
  for (int i = 1; i <= q; ++i) {
    int op;
    read(op);
    if (op == 1) {
      int x, y;
      uint k;
      read(x), read(y), read(k);
      update(x, y, k);
    } else {
      int x, y;
      read(x), read(y);
      write(query(x, y)), EL;
    }
    if (i % B == 0) {
      rebuild();
    }
  }
  return 0;
}

uint query_dfs(int x, int y) {
  if (!x) {
    return sum[y];
  }
  int lb = x & -x;
  return query_dfs(x - lb, y) - query_dfs(x - lb, y - lb);
}
uint query(int x, int y) {
  if ((x & y) != x) {
    return 0;
  }
  uint ans = 0;
  for (int i = 1; i <= top; ++i) {
    int l = x | stax[i], r = y & stay[i];
    if ((l & r) == l) {
      ans += (1u << popc[l ^ r]) * stak[i];
    }
  }
  if (popc[y ^ x] <= half) {
    int z = y ^ x;
    for (int i = z;; i = (i - 1) & z) {
      ans += val[x ^ i];
      if (!i) {
        break;
      }
    }
    return ans;
  }
  ans += query_dfs(x, y);
  return ans;
}
void update_dfs(int x, int y, uint k) {
  if (!x) {
    tags[y] += k;
    return;
  }
  int lb = x & -x;
  update_dfs(x - lb, y, k), update_dfs(x - lb, y - lb, -k);
}
void update(int x, int y, uint k) {
  if ((x & y) != x) {
    return;
  }
  ++top;
  stax[top] = x, stay[top] = y, stak[top] = k;
  if (popc[y ^ x] <= half) {
    int z = y ^ x;
    for (int i = z;; i = (i - 1) & z) {
      tagv[x ^ i] += k;
      if (!i) {
        break;
      }
    }
    return;
  }
  update_dfs(x, y, k);
}
void rebuild() {
  FWT_and(tags, n);
  for (int i = 0; i < n; ++i) {
    sum[i] = (val[i] += tagv[i] + tags[i]);
    tagv[i] = tags[i] = 0;
  }
  FWT_or(sum, n);
  top = 0;
}
void FWT_and(uint *A, int lim) {
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        A[i | j] += A[i | j | l];
      }
    }
  }
}
void FWT_or(uint *A, int lim) {
  for (int l = 1; l < lim; l <<= 1) {
    for (int i = 0; i < lim; i += (l << 1)) {
      for (int j = 0; j < l; ++j) {
        A[i | j | l] += A[i | j];
      }
    }
  }
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
