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
#define N 20
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void DFS(double, double);
double ans=inf*1.0;
double now;
int num;
int n;
bool flag[N];
double xx[N], yy[N];
int main () {
    read(n);
    for (int i=1; i<=n; ++i) {
        cin>>xx[i]>>yy[i];
    }
    DFS(0, 0);
    cout.precision(2);
    cout<<fixed<<ans<<endl;
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
void DFS(double x, double y) {
    if (num==n) {
        ans=min(ans, now);
        return;
    }
    for (int i=1; i<=n; ++i) {
        if (flag[i]==false) {
            now+=sqrt((xx[i]-x)*(xx[i]-x)+(yy[i]-y)*(yy[i]-y));
            if (now<=ans) {
                num++;
                flag[i]=true;
                DFS(xx[i], yy[i]);
                flag[i]=false;
                num--;
            }
            now-=sqrt((xx[i]-x)*(xx[i]-x)+(yy[i]-y)*(yy[i]-y));
        }
    }
}
