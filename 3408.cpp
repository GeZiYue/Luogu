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
#define N 500005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef long long int ll;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void add(int, int);
void DFS(int);
ll dp[N];
bool vis[N];
int hed[N], nxt[N], to[N], id;
ll a[N];
int n;
ll t;
int main () {
    read(n);
    read(t);
    read(a[0]);
    id=0;
    for (int i=1; i<=n; ++i) {
        int x;
        read(x);
        add(x, i);
        read(a[i]);
    }
    DFS(0);
    write(dp[0]);
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
void add(int x, int y) {
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
}
void DFS(int u) {
    if (vis[u]) {
        return;
    }
    if (!hed[u]) {
        dp[u]=a[u];
        vis[u]=true;
        return;
    }
    vector<ll>cnt;
    int num=0;
    for (int i=hed[u]; i; i=nxt[i]) {
        int v=to[i];
        DFS(v);
        cnt.push_back(dp[v]);
        ++num;
    }
    sort(cnt.begin(), cnt.end());
    num=(num*1ll*a[u]+t-1)/t;
    dp[u]=0;
    for (int i=0; i<num; ++i) {
        dp[u]+=cnt[i];
    }
    vis[u]=true;
}
