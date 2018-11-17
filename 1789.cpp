#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 105
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
const int xx1[]={-2, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 2};
const int yy1[]={0, -1, 0, 1, 2, 1, 0, -1, -2, 1, 0, -1, 0};
const int xx2[]={-2, -2, -2, -2, -2, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2};
const int yy2[]={-2, -1, 0, 1, 2, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2, -2, -1, 0, 1, 2};
bool a[N][N];
int main () {
    int n, m, k;
    read(n);
    read(m);
    read(k);
    for (int i=1; i<=m; ++i) {
        int x, y;
        read(x);
        read(y);
        for (int j=0; j<13; ++j) {
            int nx=x+xx1[j], ny=y+yy1[j];
            if (nx>=1&&ny>=1&&nx<=n&&ny<=n) {
                a[nx][ny]=true;
            }
        }
    }
    for (int i=1; i<=k; ++i) {
        int x, y;
        read(x);
        read(y);
        for (int j=0; j<25; ++j) {
            int nx=x+xx2[j], ny=y+yy2[j];
            if (nx>=1&&ny>=1&&nx<=n&&ny<=n) {
                a[nx][ny]=true;
            }
        }
    }
    int ans=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            if (!a[i][j]) {
                ++ans;
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
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch)) {
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
