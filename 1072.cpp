#include <iostream>
#include <cstdio>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
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

int gcd(int, int);

int main () {
    int t;
    read(t);
    while (t--) {
        int a0, a1, b0, b1;
        read(a0), read(a1), read(b0), read(b1);
        int p = a0 / a1, q = b1 / b0;
        int ans = 0;
        for (int i = 1; i * i <= b1; ++i) {
            if (b1 % i == 0) {
                if (i % a1 == 0) {
                    if (gcd(i / a1, p) == 1 && gcd(q, b1 / i) == 1) {
                        ++ans;
                    }
                }
                int j = b1 / i;
                if (i ^ j) {
                    if (j % a1 == 0) {
                        if (gcd(j / a1, p) == 1 && gcd(q, b1 / j) == 1) {
                            ++ans;
                        }
                    }
                }
            }
        }
        write(ans), EL;
    }
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

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
