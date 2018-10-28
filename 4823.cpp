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
#define N 2005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Node {
public:
    int x, y, sum;
    friend bool operator<(Node, Node);
}a[N];
int dp[N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i].x);
        read(a[i].y);
        a[i].sum=a[i].x+a[i].y;
    }
    int h;
    read(h);
    sort(a+1, a+n+1);
    for (int i=1; i<=n; ++i) {
        dp[i]=-inf;
    }
    for (int i=1; i<=n; ++i) {
        dp[0]+=a[i].x;
    }
    for (int i=1; i<=n; ++i) {
        for (int j=n; j>=1; --j) {
            if (dp[j-1]+a[i].y>=h) {
                dp[j]=max(dp[j], dp[j-1]-a[i].x);
            }
        }
    }
    for (int i=n; i>=0; --i) {
        if (dp[i]>=0) {
            write(i);
            EL;
            return 0;
        }
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
bool operator<(Node i, Node j) {
    return i.sum<j.sum;
}
