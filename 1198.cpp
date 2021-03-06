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
const int N = 200005;

int find(int);
void uni(int, int);

int fa[N], maxi[N];
int id;

int main () {
	int n, m;
	read(n), read(m);
    int lastans = 0;
    for (int i = 1; i <= n; ++i) {
        char ch = getchar();
        if (ch != 'A' && ch != 'Q') {
            ch = getchar();
        }
        ll a;
        read(a);
        if (ch == 'A') {
            ++id;
            fa[id] = id;
            maxi[id] = (a + lastans) % m;
            int fi = find(id);
            while (fi > 1 && maxi[fi] > maxi[find(fi - 1)]) {
                uni(fi - 1, fi);
                fi = find(id);
            }
        } else {
            lastans = maxi[find(id - a + 1)];
            write(lastans), EL;
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

int find(int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void uni(int x, int y) {
    int fx = find(x), fy = find(y);
    fa[fy] = fx;
    maxi[fx] = maxi[fy];
}
