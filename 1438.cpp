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
#define N 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class zkw {
private:
    int Sum[N<<2];
    int Add[N<<2];
    int Begin;
public:
    void Build(int);
    void Update(int, int, int);
    int Query(int, int);
}T;
int a[N];
int main () {
    int n, m;
    read(n);
    read(m);
    for (int i=1; i<=n; ++i) {
        read(a[i]);
    }
    T.Build(n);
    for (int i=1; i<=m; ++i) {
        int mode;
        read(mode);
        if (mode^2) {
            int l, r, k, d;
            read(l);
            read(r);
            read(k);
            read(d);
            T.Update(l, l, k);
            T.Update(l+1, r, d);
            if (r^n) {
                T.Update(r+1, r+1, -k-d*(r-l));
            }
        }else {
            int p;
            read(p);
            write(a[p]+T.Query(1, p));
            EL;
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
void zkw::Build(int n) {
    for (Begin=1; Begin<=n; Begin<<=1);
}
void zkw::Update(int l, int r, int num) {
    int len=1, lc=0, rc=0;
    for (l+=Begin-1, r+=Begin+1; l^r^1; l>>=1, r>>=1, len<<=1) {
        if (~l&1) {
            lc+=len, Add[l^1]+=num;
        }
        if (r&1) {
            rc+=len, Add[r^1]+=num;
        }
        Sum[l>>1]+=lc*num, Sum[r>>1]+=rc*num;
    }
    for (lc+=rc, l>>=1; l; l>>=1) {
        Sum[l]+=lc*num;
    }
}
int zkw::Query(int l, int r) {
    int ans=0;
    int len=1, lc=0, rc=0;
    for (l+=Begin-1, r+=Begin+1; l^r^1; l>>=1, r>>=1, len<<=1) {
        if (~l&1) {
            lc+=len, ans+=Sum[l^1]+len*Add[l^1];
        }
        if (r&1) {
            rc+=len, ans+=Sum[r^1]+len*Add[r^1];
        }
        ans+=lc*Add[l>>1]+rc*Add[r>>1];
    }
    for (lc+=rc, l>>=1; l; l>>=1) {
        ans+=lc*Add[l];
    }
    return ans;
}
