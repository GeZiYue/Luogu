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
#define N 105
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void DFS(int, int);
char a[N][N];
int f[N][N];
int xx[15]={0, -2, 2, -1, 1, 0, 0, 0, 0, 1, 1, -1, -1};
int xy[15]={0, 0, 0, 0, 0, -1, 1, -2, 2, 1, -1, -1, 1};
int main(){
    int n, m;
    cin>>n>>m;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            cin>>a[i][j];
        }
    }
    int ans=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            if ((a[i][j]=='#') && (f[i][j]==0)){
                DFS(i, j);
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
void DFS(int x,int y){
    if (f[x][y]==1) {
        return;
    }
    f[x][y]=1;
    for (int i=1; i<=12; ++i){
        if (a[x+xx[i]][y+xy[i]]=='#') {
            DFS(x+xx[i],y+xy[i]);
        }
    }
}
