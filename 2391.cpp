#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 1000005
#define File(a) freopen(a".in", "r", stdin) , freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int find(int);
int fa[N];
int ans[N];
int main () {
    int n, m, p, q;
    read(n);
    read(m);
    read(p);
    read(q);
    for (int i = 1; i <= n + 1; i++) {
        fa[i] = i;
    }
    for (int i = m; i >= 1; i--) {
        int x = (i * p + q) % n + 1;
        int y = (i * q + p) % n + 1;
        if (x > y) {
            swap(x, y);
        }
        x = find(x);
        while (x <= y) {
            ans[x] = i;
            fa[x] = find(x + 1);
            x = find(x + 1);
        }
    }
    for (int i = 1; i <= n; i++) {
        write(ans[i]);
        EL;
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k = 0;
    char ch = getchar();
    int flag = 1;
    while(!isNum(ch) ) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while(isNum(ch) ) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e < 0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e < 10) {
            putchar(w_r_i_t_e + '0');
        }else {
            write(w_r_i_t_e / 10);
            putchar( (w_r_i_t_e % 10) + '0');
        }
    }
}
int find(int x) {
    int p = x;
    while (p != fa[p]) {
        p = fa[p];
    }
    while (x != p) {
        int t = fa[x];
        fa[x] = p;
        x = t;
    }
    return p;
}
