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

int main() {
  getchar();
  putchar('#');
  for (int i = 1; i <= 6; ++i) {
    char c;
    c = getchar();
    if (c == '0') {
      putchar('F');
    }
    if (c == '1') {
      putchar('E');
    }
    if (c == '2') {
      putchar('D');
    }
    if (c == '3') {
      putchar('C');
    }
    if (c == '4') {
      putchar('B');
    }
    if (c == '5') {
      putchar('A');
    }
    if (c == '6') {
      putchar('9');
    }
    if (c == '7') {
      putchar('8');
    }
    if (c == '8') {
      putchar('7');
    }
    if (c == '9') {
      putchar('6');
    }
    if (c == 'A') {
      putchar('5');
    }
    if (c == 'B') {
      putchar('4');
    }
    if (c == 'C') {
      putchar('3');
    }
    if (c == 'D') {
      putchar('2');
    }
    if (c == 'E') {
      putchar('1');
    }
    if (c == 'F') {
      putchar('0');
    }
  }
  EL;
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
