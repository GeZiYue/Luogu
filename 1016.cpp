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
const int N = 505;

class Node {
public:
    double beg, end, len;
    double p;
}a[N];

int main () {
    double d1, c, d2;
    int n;
    std::cin >> d1 >> c >> d2 >> a[1].p;
    read(n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> a[i + 1].beg >> a[i + 1].p;
        a[i].end = a[i + 1].beg;
    }
    a[n + 1].end = d1;
    a[n + 2].beg = a[n + 2].end = d1;
    n += 2;
    for (int i = 1; i <= n; ++i) {
        a[i].len = a[i].end - a[i].beg;
    }
    double sum = 0;
    double now = 0;
    for (int i = 1; i < n;) {
        if (a[i].len > c * d2) {
            puts("No Solution");
            return 0;
        }
        int j;
        for (j = i + 1; a[j].p > a[i].p; ++j) ;
        if (a[j].beg - a[i].beg <= c * d2) {
            double nx = (a[j].beg - a[i].beg) / d2;
            if (nx < now) {
                now -= nx;
            } else {
                sum += (nx - now) * a[i].p;
                now = 0;
            }
            i = j;
        } else {
            sum += (c - now) * a[i].p;
            now = c - a[i].len / d2;
            ++i;
        }
    }
    std::cout.precision(2);
    std::cout << std::fixed << sum << std::endl;
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
