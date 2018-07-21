#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 10005
#define M 200005
#define inf 2147483647
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void add(int , int);
void DFS(int , bool);
int hed[N] , nxt[M] , to[M] , id;
bool vis[N] , col[N];
int ans0 , ans1;
int main () {
    int n , m , i , u , v , ans = 0;
    read(n);
    read(m);
    for (i = 1 ; i <= m ; i++) {
        read(u);
        read(v);
        add(u , v);
        add(v , u);
    }
    for (i = 1 ; i <= n ; i++) {
        if (vis[i] == false) {
            ans0 = ans1 = 0;
            DFS(i , 1);
            ans += min(ans0 , ans1);
        }
    }
    write(ans);
    EL;
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
void add(int x, int y) {
    nxt[++id] = hed[x];
    hed[x] = id;
    to[id] = y;
}
void DFS(int u , bool c) {
    if (vis[u]) {
        if (col[u] != c) {
            puts("Impossible");
            exit(0);
        }
        return;
    }
    vis[u] = true;
    col[u] = c;
    if (c) {
        ans1++;
    }else {
        ans0++;
    }
    int i , v;
    for (i = hed[u] ; i ; i = nxt[i]) {
        v = to[i];
        DFS(v , !c);
    }
}
