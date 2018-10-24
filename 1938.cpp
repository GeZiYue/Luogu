#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 445
#define M 1445
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Single_Source_Shortest_Path {
private:
    int hed[N], nxt[M], to[M], dis[M], id;
    int PointNum, EdgeNum, Source;
    int delta[N];
public:
    void Change(int n, int m, int s) {
        PointNum=n, EdgeNum=m, Source=s;
    }
    void Add(int, int, int);
    bool SPFA();
    int Query(int);
}G;
int main () {
    int p, m1, m2, n, s;
    read(p);
    read(m1);
    read(n);
    read(m2);
    read(s);
    G.Change(n<<1, m1+m2+n, s);
    for (int i=1; i<=n; ++i) {
        G.Add(i, i+n, -p);
    }
    for (int i=1; i<=m1; ++i) {
        int x, y;
        read(x);
        read(y);
        G.Add(x+n, y, 0);
    }
    for (int i=1; i<=m2; ++i) {
        int x, y, diss;
        read(x);
        read(y);
        read(diss);
        G.Add(x+n, y, diss);
    }
    if (G.SPFA()) {
        int maxi=0;
        for (int i=n+1; i<=n<<1; ++i) {
            maxi=max(maxi, -G.Query(i));
        }
        write(maxi);
        EL;
    }else {
        puts("-1");
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
void Single_Source_Shortest_Path::Add(int x, int y, int diss) {
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    dis[id]=diss;
}
bool Single_Source_Shortest_Path::SPFA() {
    queue<int>q;
    bool *flag=new bool[N];
    for (int i=1; i<=PointNum; ++i) {
        delta[i]=inf;
        flag[i]=false;
    }
    delta[Source]=0;
    q.push(Source);
    flag[Source]=true;
    while (!q.empty()) {
        int u=q.front();
        q.pop();
        for (int i=hed[u]; i; i=nxt[i]) {
            int v=to[i];
            if (delta[u]+dis[i]<delta[v]) {
                delta[v]=delta[u]+dis[i];
                if (!flag[v]) {
                    flag[v]=true;
                    q.push(v);
                }
            }
        }
        flag[u]=false;
    }
    for (int u=1; u<=PointNum; ++u) {
        if (delta[u]==inf) {
            continue;
        }
        for (int i=hed[u]; i; i=nxt[i]) {
            int v=to[i];
            if (delta[u]+dis[i]<delta[v]) {
                return false;
            }
        }
    }
    return true;
}
int Single_Source_Shortest_Path::Query(int x) {
    return delta[x];
}
