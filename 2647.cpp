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
#define inf 2147483647
#define N 3005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Node {
public:
    int w, r;
    friend bool operator<(Node, Node);
}a[N];
int dp[N][N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i].w);
        read(a[i].r);
    }
    sort(a+1, a+n+1);
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=i; ++j) {
            dp[i][j]=-inf;
        }
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=i; ++j) {
            dp[i][j]=max(dp[i-1][j], dp[i-1][j-1]+a[i].w-a[i].r*(j-1));
        }
    }
    int maxi=0;
    for (int i=1; i<=n; ++i) {
        maxi=max(maxi, dp[n][i]);
    }
    write(maxi);
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
bool operator<(Node i, Node j) {
    return i.r>j.r;
}
