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
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 100005
#define M 200005
#define inf 2147483647
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
void Dijkstra();
class Graph {
public:
    int hed[N] , nxt[M] , to[M] , dis[M] , id;
    void Add(int , int , int);
}g;
int s;
int n;
int far[N];
priority_queue<pair<int , int> >q;
int main () {
    int m;
    read(n);
    read(m);
    read(s);
    int u , v , diss;
    for (int i = 1 ; i <= m ; i++) {
        read(u);
        read(v);
        read(diss);
        g.Add(u , v , diss);
    }
    Dijkstra();
    for (int i = 1 ; i <= n ; i++) {
        write(far[i]);
        SP;
    }
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k = 0;
    char ch = getchar();
    int flag = 1;
    while(!isNum(ch) ) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while(isNum(ch) ) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e < 0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e < 10) {
            putchar(w_r_i_t_e + '0');
        }else {
            write(w_r_i_t_e / 10);
            putchar( (w_r_i_t_e % 10) + '0');
        }
    }
}
void Dijkstra() {
    for (int i = 1 ; i <= n ; i++) {
        far[i] = inf;
    }
    far[s] = 0;
    q.push(make_pair(0 , s));
    while (!q.empty()) {
        pair<int , int>Node = q.top();
        int u = Node.second , d = -Node.first;
        q.pop();
        if (d != far[u]) {
            continue;
        }
        for (int i = g.hed[u] ; i ; i = g.nxt[i]) {
            int v = g.to[i] , diss = g.dis[i];
            if (far[u] + diss < far[v]) {
                far[v] = far[u] + diss;
                q.push(make_pair(-far[v] , v));
            }
        }
    }
}
void Graph::Add(int u , int v , int diss) {
    nxt[++id] = hed[u];
    hed[u] = id;
    to[id] = v;
    dis[id] = diss;
}
