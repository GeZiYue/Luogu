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
#define N 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int a[N];
ll ans[N];
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
    }
    int m, p1, s1, s2;
    read(m);
    read(p1);
    read(s1);
    read(s2);
    a[p1]+=s1;
    ll sum=0;
    for (int i=1; i<=n; ++i) {
        sum+=(m-i)*1ll*a[i];
    }
    int mini=1;
    for (int i=1; i<=n; ++i) {
        ans[i]=sum+(m-i)*1ll*s2;
        if (abs(ans[i])<abs(ans[mini])) {
            mini=i;
        }
    }
    write(mini);
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
