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
const int N = 150005;

class Node {
public:
	int t1, t2;
}a[N];

bool cmp(const Node &i, const Node &j) {
	return i.t2 < j.t2;
}

std::priority_queue<int> pq;

int main () {
	int n;
	read(n);
	for (int i = 1; i <= n; ++i) {
		read(a[i].t1), read(a[i].t2);
	}
	std::sort(a + 1, a + n + 1, cmp);
	ll T = 0;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		if (T + a[i].t1 <= a[i].t2) {
			T += a[i].t1;
			pq.push(a[i].t1);
			++ans;
		} else {
			if (!pq.empty()) {
				int t = pq.top();
				if (t > a[i].t1 && T - t + a[i].t1 <= a[i].t2) {
					T = T - t + a[i].t1;
					pq.pop();
					pq.push(a[i].t1);
				}
			}
		}
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
