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
#define N 905
#define M 3605
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Graph {
private:
    int PointNum, EdgeNum;
    int hed[N], nxt[M], to[M], dis[M];
    int delta[N];
public:
    void Dijkstra(int);
    void Add(int, int, int);
    int Query(int);
    void Change(int);
}g;
int cnt;
int n;
int Get(int, int);
char c[N][N];
const int xx[5]={0, 1, -1, 0, 0}, yy[5]={0, 0, 0, 1, -1};
int main () {
    int a, b;
    read(n);
    read(a);
    read(b);
    int m=n*n;
    g.Change(m);
    for (int i=1; i<=n; i++) {
        cin>>(c[i]+1);
    }
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=n; j++) {
            for (int k=1; k<=4; k++) {
                int nx=i+xx[k], ny=j+yy[k];
                if (nx>=1&&ny>=1&&nx<=n&&ny<=n) {
                    ++cnt;
                    g.Add(Get(i, j), Get(nx, ny), c[nx][ny]==c[i][j]?a:b);
                }
            }
        }
    }
    int ans=0;
    for (int i=1; i<=m; ++i) {
        g.Dijkstra(i);
        for (int j=i+1; j<=m; ++j) {
            ++cnt;
            ans=max(ans, g.Query(j));
        }
    }
    write(cnt);
    EL;
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
int Get(int x, int y) {
    return (x-1)*n+y;
}
void Graph::Dijkstra(int Source) {
    priority_queue<int>q;
    for (int i=1; i<=PointNum; ++i) {
        delta[i]=inf;
    }
    delta[Source]=0;
    q.push(Source);
    while (!q.empty()) {
        int now=q.top();
        q.pop();
        for (int i=hed[now]; i; i=nxt[i]) {
            ++cnt;
            int v=to[i];
            if (delta[now]+dis[i]<delta[v]) {
                delta[v]=delta[now]+dis[i];
                q.push(v);
            }
        }
    }
}
void Graph::Add(int x, int y, int diss) {
    nxt[++EdgeNum]=hed[x];
    hed[x]=EdgeNum;
    to[EdgeNum]=y;
    dis[EdgeNum]=diss;
}
int Graph::Query(int x) {
    return delta[x];
}
void Graph::Change(int n) {
    PointNum=n;
}
