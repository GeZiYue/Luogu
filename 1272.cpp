#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 155
#define M 305
#define inf 2147483647
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void add(int, int);
void DFS(int, int);
int hed[N], nxt[M], to[M], id;
int degree[N];
int dp[N][N];
int m;
int main () {
    int n;
    read(n);
    read(m);
    int x, y;
    for (int i=1; i<n; i++) {
        read(x);
        read(y);
        add(x, y);
        add(y, x);
        degree[x]++;
        degree[y]++;
    }
    memset(dp, 0x3f, sizeof(dp));
    DFS(1, 0);
    int ans=inf;
    for (int i=1; i<=n; i++) {
        ans=min(ans, dp[i][m]);
    }
    write(ans);
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag = -1;
        }
        ch=getchar();
    }
    while (isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d = flag*k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e<0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e<10) {
            putchar(w_r_i_t_e+'0');
        }else {
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
void add(int x, int y) {
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
void DFS(int u, int fa) {
    dp[u][1]=degree[u];
    int v;
    for (int i=hed[u]; i; i=nxt[i]) {
        v=to[i];
        if (v==fa) {
            continue;
        }
        DFS(v, u);
        for (int j=m; j>=1; j--) {
            for (int k=1; k<j; k++) {
                dp[u][j]=min(dp[u][j], dp[u][k]+dp[v][j-k]-2);
            }
        }
    }
}
