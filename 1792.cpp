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

void del(int);

int pre[N], nxt[N];
int a[N];
bool flag[N];
std::priority_queue<pii> pq;

int main () {
	int n, m;
	read(n), read(m);
	if ((m << 1) > n) {
		puts("Error!");
		return 0;
	}
	for (int i = 1; i <= n; ++i) {
		read(a[i]);
		pre[i] = i - 1;
		nxt[i] = i + 1;
		flag[i] = true;
		pq.push(pii(a[i], i));
	}
	pre[1] = n;
	nxt[n] = 1;
	int ans = 0;
	for (int i = 1; i <= m; ++i) {
		while (!flag[pq.top().second]) {
			pq.pop();
		}
		pii now = pq.top();
		pq.pop();
		ans += now.first;
		a[now.second] = a[pre[now.second]] + a[nxt[now.second]] - a[now.second];
		pq.push(pii(a[now.second], now.second));
		del(pre[now.second]), del(nxt[now.second]);
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

void del(int x) {
	pre[nxt[x]] = pre[x];
	nxt[pre[x]] = nxt[x];
	flag[x] = false;
}
