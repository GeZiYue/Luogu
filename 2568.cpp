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
const int N = 10000005;

void getp(int);

int p[N], id;
int phi[N];
ll sum[N];
bool isp[N];

int main () {
    int n;
    read(n);
    getp(n);
    long long ans = 0;
    for (int i = 1; i <= id; ++i) {
        ans += sum[n / p[i]] * 2 - 1;
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

void getp(int n) {
    sum[1] = phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!isp[i]) {
            p[++id] = i;
            phi[i] = i - 1;
        }
        sum[i] = sum[i - 1] + phi[i];
        for (int j = 1; j <= id && i * p[j] <= n; ++j) {
            isp[i * p[j]] = true;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            } else {
                phi[i * p[j]] = phi[i] * (p[j] - 1);
            }
        }
    }
}
