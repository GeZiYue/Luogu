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
#define R register
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
int exgcd(int, int, int&, int&);
int main () {
	int a, b;
	read(a);
	read(b);
	int x, y;
	int k=exgcd(a, b, x, y);
	write(k);
	EL;
	x+=b;
	y-=a;
	int n=(x-1)/(b/k)+1;
	x-=n*(b/k);
	y+=n*(a/k);
	write(-x);
	SP;
	write(y);
	EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch) ) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
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
int exgcd(int a, int b, int& x, int& y) {
	if (b==0) {
		x=1;
		y=0;
		return a;
	}
	int k=exgcd(b, a%b, y, x);
	y-=a/b*x;
	return k;
}
