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
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
bool check(int, int);
char ch[15];
short k[15];
int main () {
    cin>>(ch+1);
    int n=strlen(ch+1);
    memset(k, -1, sizeof(k));
    for (int i=1; i<=n; ++i) {
        k[ch[i]-'0']=i&1;
    }
    int ans=-1;
    if (check(1, 1)||check(1, 3)||check(1, 4)) {
        ans=k[1];
    }
    if (check(4, 1)) {
        ans=k[4];
    }
    if (check(7, 1)) {
        ans=k[7];
    }
    if (check(2, 3)) {
        ans=k[2];
    }
    if (check(3, 2)||check(3, 3)) {
        ans=k[3];
    }
    if (ans==-1) {
        puts("drew.");
    }else {
        if (ans==0) {
            puts("uim wins.");
        }else {
            puts("xiaoa wins.");
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
bool check(int b, int t) {
    return (k[b]==k[b+t])&&(k[b]==k[b+(t<<1)])&&(k[b]!=-1);
}
