#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 10
#define ll long long int
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
void DFS(int, ll, int, int);
ll n, maxn;
int maxf;
const int prime[N+5]={0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int main() {
    cin>>n;
    maxn=maxf=0;
    DFS(1, 1, 1, 20);
    write(maxn);
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
void DFS(int x, ll sum, int k, int inf) {
    if(k>maxf) {
        maxf=k;
        maxn=sum;
    }
    if(k==maxf&&sum<maxn) {
        maxn=sum;
    }
    if(x>N) {
        return;
    }
    int i;
    ll now=sum;
    for(i=1; i<=inf; i++) {
        now*=prime[x];
        if(now>n) {
            break;
        }
        DFS(x+1, now, k*(i+1), i);
    }
}
