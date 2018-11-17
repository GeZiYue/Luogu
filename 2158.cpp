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
#define N 40005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void Prime(int);
int Pr[N], id;
bool isP[N];
int phi[N];
int main () {
    int n;
    read(n);
    if (n==1) {
        write(0);
        EL;
        return 0;
    }
    Prime(n);
    int ans=3;
    for (int i=2; i<n; ++i) {
        ans+=phi[i]*2;
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
void Prime(int n) {
    phi[1]=1;
    for (int i=2; i<=n; ++i) {
        if (!isP[i]) {
            phi[i]=i-1;
            Pr[++id]=i;
        }
        for (int j=1; j<=id&&Pr[j]*i<=n; ++j) {
            isP[i*Pr[j]]=true;
            if (i%Pr[j]==0) {
                phi[i*Pr[j]]=phi[i]*Pr[j];
                break;
            }
            phi[i*Pr[j]]=phi[i]*phi[Pr[j]];
        }
    }
}
