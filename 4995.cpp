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
#define N 305
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
ll a[N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
    }
    sort(a+1, a+n+1, greater<int>());
    ll ans=0;
    for (int i=1, j=n; i<=j; ++i, --j) {
        ans+=(a[i]-a[j+1])*(a[i]-a[j+1]);
        if (i!=j) {
            ans+=(a[i]-a[j])*(a[i]-a[j]);
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
