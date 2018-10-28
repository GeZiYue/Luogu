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
#define M 4000005
#define Mod 100003
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void Add(int, int);
int hed[N], nxt[M], to[M], id;
int dep[N], ans[N];
queue<int>q;
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=m; ++i) {
        int x, y;
        read(x);
        read(y);
        Add(x, y);
        Add(y, x);
    }
    q.push(1);
    dep[1]=1;
    ans[1]=1;
    while (!q.empty()) {
        int u=q.front();
        q.pop();
        for (int i=hed[u]; i; i=nxt[i]) {
            int v=to[i];
            if (!dep[v]) {
                dep[v]=dep[u]+1;
                q.push(v);
            }
            if (dep[v]==dep[u]+1) {
                ans[v]=(ans[v]+ans[u])%Mod;
            }
        }
    }
    for (int i=1; i<=n; ++i) {
        write(ans[i]);
        EL;
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
void Add(int x, int y) {
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
