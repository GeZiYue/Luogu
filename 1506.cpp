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
#define N 505
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void DFS(int, int);
const int xx[5]={0, 1, -1, 0, 0}, yy[5]={0, 0, 0, 1, -1};
char a[N][N];
bool f[N][N];
int n, m;
int main () {
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            cin>>a[i][j];
            if (a[i][j]=='*') {
                f[i][j]=true;
            }
        }
    }
    DFS(0, 0);
    int ans=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            if (f[i][j]==false) {
                ans++;
            }
        }
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
void DFS(int x, int y) {
    if (f[x][y]) {
        return;
    }
    f[x][y]=true;
    for (int i=1; i<=4; ++i) {
        int nx=x+xx[i], ny=y+yy[i];
        if (nx<0||ny<0||nx>n+1||ny>m+1) {
            continue;
        }
        DFS(nx, ny);
    }
}
