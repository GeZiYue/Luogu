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
#define isLet(a) ((a>='a'&&a<='z')||(a>='A'&&a<='Z'))
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
string str;
int main () {
    int n, p1, p2, p3;
    read(p1);
    read(p2);
    read(p3);
    cin>>str;
    n=str.size();
    putchar(str[0]);
    for (int i=1; i<n-1; i++) {
        if (str[i]=='-'&&str[i+1]>str[i-1]&&((isNum(str[i+1])&&isNum(str[i-1]))||
        (isLet(str[i+1])&&isLet(str[i-1])))) {
            for (char j=(p3==1?(str[i-1]+1):(str[i+1]-1)); (p3==1)?(j<=str[i+1]-1):(j>=str[i-1]+1); (p3==1?(++j):(--j))) {
                char now=j;
                if (p1==2) {
                    now=isLet(j)?j-'a'+'A':j;
                }else {
                    if (p1==3) {
                        now='*';
                    }
                }
                for (int k=1; k<=p2; ++k) {
                    putchar(now);
                }
            }
        }else {
            putchar(str[i]);
        }
    }
    putchar(str[n-1]);
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
