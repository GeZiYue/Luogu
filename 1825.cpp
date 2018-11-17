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
#define N 90005
#define M 400005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef pair<int, int> P;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Graph {
private:
    int hed[N], nxt[M], to[M], wei[M];
public:
    int EdgeNum, PointNum;
    int delta[N];
    void Add(int, int, int);
    void Dijkstra(int);
}G;
const int xx[5]={0, 0, 0, 1, -1}, yy[5]={0, 1, -1, 0, 0};
int Change(P);
P fir[30];
P sec[30];
int sum[30];
char ch[305][305];
int n, m;
int main () {
    read(n);
    read(m);
    G.PointNum=n*m;
    int beg, end;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            ch[i][j]=getchar();
            if (ch[i][j]>='A'&&ch[i][j]<='Z') {
                if (sum[ch[i][j]-'A']) {
                    sec[ch[i][j]-'A']=P(i, j);
                }else {
                    fir[ch[i][j]-'A']=P(i, j);
                }
                ++sum[ch[i][j]-'A'];
            }
            if (ch[i][j]=='@') {
                beg=Change(P(i, j));
            }
            if (ch[i][j]=='=') {
                end=Change(P(i, j));
            }
        }
        getchar();
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=m; ++j) {
            if (ch[i][j]=='#') {
                continue;
            }
            for (int k=1; k<=4; ++k) {
                int nx=i+xx[k], ny=j+yy[k];
                if (nx>=1&&nx<=n&&ny>=1&&ny<=m&&ch[nx][ny]!='#') {
                    P now(nx, ny);
                    if (ch[nx][ny]>='A'&&ch[nx][ny]<='Z'&&sum[ch[nx][ny]-'A']>1) {
                        if (P(nx, ny)==fir[ch[nx][ny]-'A']) {
                            now=sec[ch[nx][ny]-'A'];
                        }else {
                            now=fir[ch[nx][ny]-'A'];
                        }
                    }
                    G.Add(Change(P(i, j)), Change(now), 1);
                }
            }
        }
    }
    G.Dijkstra(beg);
    write(G.delta[end]);
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
int Change(P x) {
    return (x.first-1)*m+x.second;
}
void Graph::Add(int x, int y, int dis) {
    nxt[++EdgeNum]=hed[x];
    hed[x]=EdgeNum;
    to[EdgeNum]=y;
    wei[EdgeNum]=dis;
}
void Graph::Dijkstra(int Source) {
    for (int i=1; i<=PointNum; ++i) {
        delta[i]=inf;
    }
    delta[Source]=0;
    priority_queue<P, vector<P>, greater<P> >q;
    q.push(P(0, Source));
    while (!q.empty()) {
        P now=q.top();
        q.pop();
        if (now.first!=delta[now.second]) {
            continue;
        }
        int u=now.second;
        for (int i=hed[u]; i; i=nxt[i]) {
            int v=to[i];
            if (delta[u]+wei[i]<delta[v]) {
                delta[v]=delta[u]+wei[i];
                q.push(P(delta[v], v));
            }
        }
    }
}
