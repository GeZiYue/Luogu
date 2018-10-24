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
#define N 1005
#define M 100005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
class Single_Sourse_Shortest_Path {
private:
    int hed[N], nxt[M], to[M], dis[M];
    int id;
    int PointNum, EdgeNum, Sourse;
    int delta[N];
public:
    void Change(int n, int m, int s){
        PointNum=n;
        EdgeNum=m;
        Sourse=s;
    }
    void Add(int, int, int);
    void Dijkstra();
    int Query(int);
}bef, aft;
int main () {
    int n, m, s;
    read(n);
    read(m);
    read(s);
    bef.Change(n, m, s);
    aft.Change(n, m, s);
    for (int i=1; i<=m; ++i) {
        int x, y, diss;
        read(x);
        read(y);
        read(diss);
        bef.Add(x, y, diss);
        aft.Add(y, x, diss);
    }
    bef.Dijkstra();
    aft.Dijkstra();
    int maxi=0;
    for (int i=1; i<=n; ++i) {
        if (i==s) {
            continue;
        }
        maxi=max(maxi, bef.Query(i)+aft.Query(i));
    }
    write(maxi);
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
void Single_Sourse_Shortest_Path::Add(int x, int y, int diss) {
    nxt[++id]=hed[x];
    hed[x]=id;
    to[id]=y;
    dis[id]=diss;
}
void Single_Sourse_Shortest_Path::Dijkstra() {
    priority_queue<int>q;
    for (int i=1; i<=PointNum; i++) {
        delta[i]=inf;
    }
    delta[Sourse]=0;
    q.push(Sourse);
    while (!q.empty()) {
        int u=q.top();
        q.pop();
        for (int i=hed[u]; i; i=nxt[i]) {
            int v=to[i];
            if (delta[u]+dis[i]<delta[v]) {
                delta[v]=delta[u]+dis[i];
                q.push(v);
            }
        }
    }
}
int Single_Sourse_Shortest_Path::Query(int x) {
    return delta[x];
}
