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
#define inf 2147483647
#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

template <class T>
inline void read(T &);
template <class T>
inline void write(const T &);

typedef long long ll;
typedef const long long & cll;
typedef const int & ci;

const int N = 100005;

class Node {
public:
    int siz, v, ch[2], fa;
    bool tag;
    Node(int v = 0) : v(v) {
        ch[0] = ch[1] = fa = tag = 0;
    }
};

class Splay {
private:
    Node *T;
    int cnt;
    void pushup(int);
    void pushdown(int);
    bool getid(int);
    void connect(int, int, bool);
    void rotate(int);
    void splay(int, int);
    int find(int);
public:
    int root;
    Splay() {
        T = new Node[N];
        cnt = 0;
    }
    ~Splay() {
        delete[] T;
    }
    int build(int, int, int, int *);
    void reserve(int, int);
    void print(int);
} S;

int a[N];
int main() {
    int n, m;
    read(n), read(m);
    a[1] = -inf, a[n + 2] = inf;
    for (int i = 1; i <= n; ++i) {
        a[i + 1] = i;
    }
    S.build(1, n + 2, 0, a);
    S.root = 1;
    for (int i = 1; i <= m; ++i) {
        int l, r;
        read(l), read(r);
        S.reserve(l, r);
    }
    S.print(S.root);
    EL;
    return 0;
}

template <class T>
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
template <class T>
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

void Splay::pushup(int x) {
    if (!x) {
        return;
    }
    T[x].siz = 1;
    if (T[x].ch[0]) {
        T[x].siz += T[T[x].ch[0]].siz;
    }
    if (T[x].ch[1]) {
        T[x].siz += T[T[x].ch[1]].siz;
    }
}
void Splay::pushdown(int x) {
    if (x && T[x].tag) {
        std::swap(T[x].ch[0], T[x].ch[1]);
        T[T[x].ch[0]].tag ^= 1;
        T[T[x].ch[1]].tag ^= 1;
        T[x].tag = false;
    }
}
bool Splay::getid(int x) {
    return T[T[x].fa].ch[1] == x;
}
void Splay::connect(int x, int fa, bool how) {
    T[x].fa = fa;
    T[fa].ch[how] = x;
}
void Splay::rotate(int x) {
    int y = T[x].fa;
    int R = T[y].fa;
    int yson = getid(x), Rson = getid(y);
    connect(T[x].ch[yson ^ 1], y, yson);
    connect(y, x, yson ^ 1);
    connect(x, R, Rson);
    pushup(y), pushup(x);
}
void Splay::splay(int x, int to) {
    while (T[x].fa != to) {
        if (T[T[x].fa].fa ^ to) {
            rotate(getid(x) == getid(T[x].fa) ? T[x].fa : x);
        }
        rotate(x);
    }
    if (to == 0) {
        root = x;
    }
}
int Splay::find(int k) {
    int x = root;
    while (true) {
        pushdown(x);
        int now = T[T[x].ch[0]].siz + 1;
        if (now == k) {
            return x;
        }
        if (now < k) {
            k -= now;
            x = T[x].ch[1];
        } else {
            x = T[x].ch[0];
        }
    }
}
int Splay::build(int xL, int xR, int fa, int *x) {
    if (xL > xR) {
        return 0;
    }
    int xM = (xL + xR) >> 1;
    int now = ++cnt;
    T[now].v = x[xM];
    T[now].fa = fa;
    T[now].ch[0] = build(xL, xM - 1, now, x);
    T[now].ch[1] = build(xM + 1, xR, now, x);
    T[now].siz = xR - xL + 1;
    return now;
}
void Splay::reserve(int l, int r) {
    l = find(l), r = find(r + 2);
    splay(l, 0), splay(r, root);
    T[T[r].ch[0]].tag ^= 1;
}
void Splay::print(int x) {
    if (!x) {
        return;
    }
    pushdown(x);
    print(T[x].ch[0]);
    if (abs(T[x].v) ^ inf) {
        write(T[x].v), SP;
    }
    print(T[x].ch[1]);
}
