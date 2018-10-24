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
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
double inline f(double);
double inline dvt_f(double);
double inline solve(double);
double a, b, c, d;
double ans[5];
int id;
int main () {
    cin>>a>>b>>c>>d;
    cout.precision(2);
    for (double i=-100.0; i<=100.0; i+=0.5) {
        double now=solve(i);
        bool flag=true;
        for (int j=1; j<=id; ++j) {
            if (abs(ans[j]-now)<=0.5) {
                flag=false;
            }
        }
        if (flag) {
            ans[++id]=now;
        }
    }
    sort(ans+1, ans+4);
    cout<<fixed<<ans[1]<<' '<<ans[2]<<' '<<ans[3]<<endl;
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
double f(double x) {
    return ((a*x+b)*x+c)*x+d;
}
double dvt_f(double x) {
    return (a*3*x+b*2)*x+c;
}
double solve(double a) {
    while (abs(f(a))>=0.00001) {
        a=a-f(a)/dvt_f(a);
    }
    return a;
}
