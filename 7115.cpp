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

const int N = 55;
const int M = 405;
typedef std::pair<int, int> pii;

void chg(int x, int y);
int find();
void work(std::vector<int> V, int cl, int cr);

int a[N][M], siz[N], emp;
int c[N][M];
std::vector<pii> ans;
int n, m;

int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      read(a[i][j]);
    }
    siz[i] = m;
  }
  emp = n + 1;
  std::vector<int> V;
  for (int i = 1; i <= n; ++i) {
    V.push_back(i);
  }
  work(V, 1, n);
  write(ans.size()), EL;
  for (int i = 0; i < (int)ans.size(); ++i) {
    write(ans[i].first), SP, write(ans[i].second), EL;
  }
  return 0;
}

void chg(int x, int y) {
  a[y][siz[y] + 1] = a[x][siz[x]];
  c[y][siz[y] + 1] = c[x][siz[x]];
  ++siz[y], --siz[x];
  ans.push_back(pii(x, y));
}
int find() {
  for (int i = 1; i <= n; ++i) {
    if (siz[i] == 0) {
      return emp = i;
    }
  }
  return 0;
}
pii solve(int x, int y) {
  int cnt0 = 0, cnt1 = 0;
  for (int i = 1; i <= m; ++i) {
    if (c[x][i] == 0) {
      ++cnt0;
    } else {
      ++cnt1;
    }
    if (c[y][i] == 0) {
      ++cnt0;
    } else {
      ++cnt1;
    }
  }
  int qwq;
  if (cnt0 >= cnt1) {
    qwq = 0;
  } else {
    qwq = 1;
  }
  int ctx = 0, cty = 0;
  for (int i = 1; i <= m; ++i) {
    if (c[x][i] == qwq) {
      ++ctx;
    }
    if (c[y][i] == qwq) {
      ++cty;
    }
  }
  if (ctx == m) {
    return pii(x, qwq);
  }
  if (cty == m) {
    return pii(y, qwq);
  }
  for (int i = 1; i <= ctx; ++i) {
    chg(y, emp);
  }
  for (int i = m; i >= 1; --i) {
    if (c[x][i] == qwq) {
      chg(x, y);
    } else {
      chg(x, emp);
    }
  }
  for (int i = 1; i <= m - ctx; ++i) {
    chg(emp, x);
  }
  for (int i = 1; i <= ctx; ++i) {
    chg(y, x);
  }
  for (int i = 1; i <= ctx; ++i) {
    chg(emp, y);
  }
  for (int i = 1; i <= ctx; ++i) {
    chg(x, emp);
  }
  for (int i = m; i >= 1; --i) {
    if (c[y][i] == qwq && siz[emp] < m) {
      chg(y, emp);
    } else {
      chg(y, x);
    }
  }
  for (int i = 1; i <= m; ++i) {
    chg(emp, y);
  }
  return pii(y, qwq);
}

void print() {
  for (int i = 1; i <= n + 1; ++i) {
    for (int j = 1; j <= siz[i]; ++j) {
      write(a[i][j]), SP;
    }
    EL;
  }
  for (int i = 1; i <= n + 1; ++i) {
    for (int j = 1; j <= siz[i]; ++j) {
      write(c[i][j]), SP;
    }
    EL;
  }
}
void work(std::vector<int> V, int cl, int cr) {
  if (cl == cr) {
    return;
  }
  int cm = (cl + cr) >> 1;
  for (std::vector<int>::iterator it = V.begin(); it != V.end(); ++it) {
    int x = *it;
    for (int j = 1; j <= m; ++j) {
      if (a[x][j] <= cm) {
        c[x][j] = 0;
      } else {
        c[x][j] = 1;
      }
    }
  }
  std::vector<int> V0, V1;
  for (int i = 0; i < (int)V.size() - 1; ++i) {
    pii now = solve(V[i], V[i + 1]);
    if (now.first == V[i + 1]) {
      std::swap(V[i], V[i + 1]);
    }
    if (now.second == 0) {
      V0.push_back(V[i]);
    } else {
      V1.push_back(V[i]);
    }
  }
  bool flag = true;
  for (int i = 1; i <= m; ++i) {
    if (c[V[V.size() - 1]][i] == 1) {
      flag = false;
      break;
    }
  }
  if (flag) {
    V0.push_back(V[V.size() - 1]);
  } else {
    V1.push_back(V[V.size() - 1]);
  }
  work(V0, cl, cm), work(V1, cm + 1, cr);
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
