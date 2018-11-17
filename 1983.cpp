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
#define N 1005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
vector<int>Edge[N<<1];
int indgree[N<<1];
int dep[N<<1];
int a[N];
queue<int>q;
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=m; ++i) {
        int siz;
        read(siz);
        for (int j=1; j<=siz; ++j) {
            read(a[j]);
            Edge[a[j]].push_back(n+i);
            ++indgree[n+i];
        }
        for (int j=1; j<siz; ++j) {
            for (int k=a[j]+1; k<a[j+1]; ++k) {
                Edge[n+i].push_back(k);
                ++indgree[k];
            }
        }
    }
    for (int i=1; i<=(n<<1); ++i) {
        if (!indgree[i]) {
            q.push(i);
            dep[i]=1;
        }
    }
    while (!q.empty()) {
        int u=q.front();
        q.pop();
        for (unsigned i=0; i<Edge[u].size(); ++i) {
            int v=Edge[u][i];
            if (v>n) {
                dep[v]=max(dep[v], dep[u]+1);
            }else {
                dep[v]=max(dep[v], dep[u]);
            }
            --indgree[v];
            if (!indgree[v]) {
                q.push(v);
            }
        }
    }
    int ans=0;
    for (int i=1; i<=n; ++i) {
        ans=max(ans, dep[i]);
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
