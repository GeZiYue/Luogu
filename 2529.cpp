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

void div5();

char ch[105];
int a[105];
int len;
int f[25] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8, 4, 4, 8, 4, 6, 8, 8, 6, 8, 2};

int main () {
    for (int i = 1; i <= 5; ++i) {
        scanf("%s", ch + 1);
        len = strlen(ch + 1);
        for (int i = 1; i <= len; ++i) {
            a[i] = ch[len - i + 1] - '0';
        }
        int ans = 1;
        while (len > 1) {
            ans = ans * f[a[2] % 2 * 10 + a[1]] % 10;
            int num = 0;
            for (int i = len; i >= 1; --i) {
                a[i] = num * 10 + a[i];
                num = a[i] % 5;
                a[i] /= 5;
            }
            while (len && !a[len]) {
                --len;
            }
        }
        ans = ans * f[a[1]] % 10;
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
