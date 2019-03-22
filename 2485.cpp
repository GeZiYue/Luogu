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

int pow(int, int, int);

int main () {
    int t, k;
    read(t), read(k);
    while (t--) {
        int y, z, p;
        read(y), read(z), read(p);
        y %= p;
        if (k == 1) {
            write(pow(y, z, p)), EL;
        } else {
            if (k == 2) {
                z %= p;
                if (y == 0 && z) {
                    puts("Orz, I cannot find x!");
                    continue;
                }
                write(z * 1ll * pow(y, p - 2, p) % p), EL;
            } else {
                if (y == 0) {
                    if (z == 0) {
                        write(1), EL;
                    } else {
                        puts("Orz, I cannot find x!");
                    }
                    continue;
                }
                std::map<int, int> mp;
                int m = sqrt(p);
                int k = z % p;
                mp[k] = 0;
                for (int i = 1; i <= m; ++i) {
                    k = k * 1ll * y % p;
                    mp[k] = i;
                }
                int mm = pow(y, m, p);
                k = 1;
                bool flag = false;
                for (int i = 1; i * i <= p; ++i) {
                    k = k * 1ll * mm % p;
                    if (mp.count(k)) {
                        write((i * 1ll * m % p - mp[k] + p) % p), EL;
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    puts("Orz, I cannot find x!");
                }
            }
        }
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

int pow(int a, int b, int mod) {
    int now = a % mod, ans = 1;
    while (b) {
        if (b & 1) {
            ans = ans * 1ll * now % mod;
        }
        now = now * 1ll * now % mod;
        b >>= 1;
    }
    return ans;
}
