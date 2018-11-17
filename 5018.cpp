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
#define N 1000005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void DFS(int);
bool Check(int, int);
int v[N];
int l[N], r[N];
int sum[N];
int ans=1;
int main () {
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        read(v[i]);
    }
    for (int i=1; i<=n; ++i) {
        read(l[i]);
        read(r[i]);
        if (l[i]==-1) {
            l[i]=0;
        }
        if (r[i]==-1) {
            r[i]=0;
        }
    }
    DFS(1);
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
void DFS(int x) {
    if (x==0) {
        return;
    }
    DFS(l[x]);
    DFS(r[x]);
    sum[x]=1+sum[l[x]]+sum[r[x]];
    if (Check(l[x], r[x])) {
        ans=max(ans, sum[x]);
    }
}
bool Check(int L, int R) {
    if (v[L]^v[R]||sum[L]^sum[R]) {
        return false;
    }
    if (L==0) {
        return true;
    }
    return Check(l[L], r[R])&Check(r[L], l[R]);
}
