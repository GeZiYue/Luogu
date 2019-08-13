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
typedef unsigned long long ull;
typedef const int& ci;
typedef std::pair<int, int> pii;
const int iinf = 2147483647;
const ll llinf = 9223372036854775807ll;
using std::min;
using std::max;
using std::abs;
using std::sort;
const int N = 100005;
const int M = 500005;

class Node {
public:
    ll d;
    int id;
    Node(ll _d, int _id) : d(_d), id(_id) {}
    bool operator < (const Node &i) const {
        return d > i.d;
    }
};

void add(int, int, int);
void dijkstra(int);

int hed[N], nxt[M], to[M], w[M], id;
std::priority_queue<Node> pq;
ll dis[N][2];
int col[N][2];
int key[N], k;
int beg[M], end[M], val[M];
bool vis[N];
int n;

int main () {
    int t;
    read(t);
    while (t--) {
        int m;
        read(n), read(m), read(k);
        id = 0;
        memset(hed, 0, sizeof(hed));
        for (int i = 1; i <= m; ++i) {
            read(beg[i]), read(end[i]), read(val[i]);
            if (beg[i] ^ end[i]) {
                add(beg[i], end[i], val[i]);
            }
        }
        for (int i = 1; i <= k; ++i) {
            read(key[i]);
        }
        dijkstra(0);
        id = 0;
        memset(hed, 0, sizeof(hed));
        for (int i = 1; i <= m; ++i) {
            if (beg[i] ^ end[i]) {
                add(end[i], beg[i], val[i]);
            }
        }
        dijkstra(1);
        ll ans = llinf;
        for (int i = 1; i <= m; ++i) {
            int u = beg[i], v = end[i], d = val[i];
            if (col[u][0] && col[v][1] && col[u][0] ^ col[v][1]) {
                ans = min(ans, dis[u][0] + dis[v][1] + d);
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

void add(int u, int v, int dis) {
    nxt[++id] = hed[u];
    hed[u] = id;
    w[id] = dis;
    to[id] = v;
}
void dijkstra(int id) {
    for (int i = 1; i <= n; ++i) {
        dis[i][id] = 1e17;
        col[i][id] = 0;
        vis[i] = false;
    }
    for (int i = 1; i <= k; ++i) {
        dis[key[i]][id] = 0;
        col[key[i]][id] = key[i];
        pq.push(Node(0, key[i]));
    }
    while (!pq.empty()) {
        Node now = pq.top();
        pq.pop();
        int u = now.id;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        for (int i = hed[u]; i; i = nxt[i]) {
            int v = to[i];
            if (dis[u][id] + w[i] < dis[v][id]) {
                dis[v][id] = dis[u][id] + w[i];
                col[v][id] = col[u][id];
                pq.push(Node(dis[v][id], v));
            }
        }
    }
}
