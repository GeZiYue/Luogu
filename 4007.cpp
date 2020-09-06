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
#include <ctime>
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
typedef unsigned long long ull;
typedef const long long & cll;
typedef const int & ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;

const int N = 62;
const int M = 170;
const int K = 9;
const int Mod = 998244353;

class Matrix {
public:
  int a[M][M];
  Matrix();
  Matrix & operator =(Matrix m);
  int* operator[](int i);
  Matrix & operator *=(Matrix m);
};

__int128 tmp[M][M];
int id[K][K][K], cnt;
int inv[K * 3];
Matrix mtx[N];
int ans[N];
int m, k, T;
ll n;

int main () {
  read(T), read(m), read(k);
  inv[1] = 1;
  for (int i = 2; i <= k * 3 + 1; ++i) {
    inv[i] = (Mod - Mod / i) * 1ll * inv[Mod % i] % Mod;
  }
  for (int a = 0; a <= k; ++a) {
    for (int b = 0; b <= k; ++b) {
      if (a + b > k) {
        continue;
      }
      if (m <= 1 && b) {
        continue;
      }
      for (int c = 0; c <= k; ++c) {
        if (a + b + c > k) {
          continue;
        }
        if (m <= 2 && c) {
          continue;
        }
        id[a][b][c] = ++cnt;
      }
    }
  }
  ++cnt;
  mtx[0][cnt][cnt] = 1;
  for (int a = 0; a <= k; ++a) {
    for (int b = 0; b <= k; ++b) {
      if (a + b > k) {
        continue;
      }
      if (m <= 1 && b) {
        continue;
      }
      for (int c = 0; c <= k; ++c) {
        if (a + b + c > k) {
          continue;
        }
        if (m <= 2 && c) {
          continue;
        }
        int in = id[a][b][c], iv = inv[a + b + c + 1];
        bool flag = a + b + c < k;
        if (m == 1) {
          if (a) {
            mtx[0][in][id[a - 1][b][c]] = a * 1ll * iv % Mod;
          }
        }
        if (m == 2) {
          if (a) {
            mtx[0][in][id[a - 1][b][c]] = a * 1ll * iv % Mod;
          }
          if (b) {
            mtx[0][in][id[a + 1][b - 1 + flag][c]] = b * 1ll * iv % Mod;
          }
        }
        if (m == 3) {
          if (a) {
            mtx[0][in][id[a - 1][b][c]] = a * 1ll * iv % Mod;
          }
          if (b) {
            mtx[0][in][id[a + 1][b - 1][c + flag]] = b * 1ll * iv % Mod;
          }
          if (c) {
            mtx[0][in][id[a][b + 1][c - 1 + flag]] = c * 1ll * iv % Mod;
          }
        }
        mtx[0][in][in] = mtx[0][in][cnt] = iv;
      }
    }
  }
  for (int i = 1; i < 60; ++i) {
    mtx[i] = mtx[i - 1];
    mtx[i] *= mtx[i - 1];
  }
  while (T--) {
    read(n);
    for (int i = 1; i <= cnt; ++i) {
      ans[i] = 0;
    }
    ans[id[m == 1][m == 2][m == 3]] = 1;
    for (int bit = 0 ; bit < 60; ++bit) {
      if (n & (1ll << bit)) {
        for (int i = 1; i <= cnt; ++i) {
          tmp[0][i] = 0;
        }
        for (int i = 1; i <= cnt; ++i) {
          int r = ans[i];
          for (int j = 1; j <= cnt; ++j) {
            tmp[0][j] += r * 1ll * mtx[bit][i][j];
          }
        }
        for (int i = 1; i <= cnt; ++i) {
          ans[i] = tmp[0][i] % Mod;
        }
      }
    }
    write(ans[cnt]), EL;
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

Matrix::Matrix() {
  for (int i = 1; i < M; ++i) {
    for (int j = 1; j < M; ++j) {
      a[i][j] = 0;
    }
  }
}
Matrix & Matrix::operator=(Matrix m) {
  for (int i = 1; i <= cnt; ++i) {
    for (int j = 1; j <= cnt; ++j) {
      a[i][j] = m[i][j];
    }
  }
  return *this;
}
int* Matrix::operator[](int i) {
  return a[i];
}
Matrix & Matrix::operator*=(Matrix m) {
  for (int i = 1; i <= cnt; ++i) {
    for (int j = 1; j <= cnt; ++j) {
      tmp[i][j] = 0;
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    for (int k = 1; k <= cnt; ++k) {
      int r = a[i][k];
      for (int j = 1; j <= cnt; ++j) {
        tmp[i][j] += r * 1ll * m[k][j];
      }
    }
  }
  for (int i = 1; i <= cnt; ++i) {
    for (int j = 1; j <= cnt; ++j) {
      a[i][j] = tmp[i][j] % Mod;
    }
  }
  return *this;
}
