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
#define N 105
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int x_1[N], y_1[N], x_2[N], y_2[N];
int main () {
    int n, m, x, y;
    read(n);
    read(m);
    read(x);
    read(y);
    for (int i=1; i<=x; ++i) {
        read(x_1[i]);
        read(y_1[i]);
        read(x_2[i]);
        read(y_2[i]);
    }
    for (int i=1; i<=y; ++i) {
        int xx, yy;
        read(xx);
        read(yy);
        int sum=0, ans=0;
        for (int j=1; j<=x; ++j) {
            if (x_1[j]<=xx&&x_2[j]>=xx&&y_1[j]<=yy&&y_2[j]>=yy) {
                ++sum;
                ans=j;
            }
        }
        if (sum) {
            putchar('Y');
            SP;
            write(sum);
            SP;
            write(ans);
        }else {
            putchar('N');
        }
        EL;
    }
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
