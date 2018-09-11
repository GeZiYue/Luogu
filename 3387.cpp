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
#define N 10005
#define M 100005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void Tarjan(int);
void DFS(int);
class Gragh {
public:
    int id;
    int hed[N] , nxt[M] , to[M];
    void Add(int , int);
}pre , aft;
int dfn[N] , low[N] , id;
int sta[N] , top;
int col[N] , sum[N] , cid;
int w[N];
int dp[N];
bool vis[N];
int main () {
    int n , m;
    read(n);
    read(m);
    for (int i = 1 ; i <= n ; i++) {
        read(w[i]);
    }
    for (int i = 1 ; i <= m ; i++) {
        int u , v;
        read(u);
        read(v);
        pre.Add(u , v);
    }
    for (int i = 1 ; i <= n ; i++) {
        if (!dfn[i]) {
            Tarjan(i);
        }
    }
    for (int u = 1 ; u <= n ; u++) {
        for (int i = pre.hed[u] ; i ; i = pre.nxt[i]) {
            int v = pre.to[i];
            if (col[u] != col[v]) {
                aft.Add(col[u] , col[v]);
            }
        }
    }
    int ans = 0;
    for (int i = 1 ; i <= cid ; i++) {
        if (dp[i] == 0) {
            DFS(i);
            ans = max(ans , dp[i]);
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
void Gragh::Add(int u , int v) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
}
void Tarjan(int u) {
    dfn[u] = low[u] = ++id;
    sta[++top] = u;
    vis[u] = true;
    for (int i = pre.hed[u] ; i ; i = pre.nxt[i]) {
        int v = pre.to[i];
        if (!dfn[v]) {
            Tarjan(v);
            low[u] = min (low[u] , low[v]);
        }else {
            if (vis[v]) {
                low[u] = min(low[u] , dfn[v]);
            }
        }
    }
    if (low[u] == dfn[u]) {
        cid++;
        while(sta[top + 1] != u) {
            int v = sta[top];
            vis[v] = false;
            col[v] = cid;
            sum[cid] += w[v];
            top--;
        }
    }
}
void DFS(int u) {
    for (int i = aft.hed[u] ; i ; i = aft.nxt[i]) {
        int v = aft.to[i];
        if (dp[v] == 0) {
            DFS(v);
        }
        dp[u] = max(dp[u] , dp[v]);
    }
    dp[u] += sum[u];
}
