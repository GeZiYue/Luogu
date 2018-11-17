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
#include<ctime>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 605
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
typedef pair<int, int> P;
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
const int xx[]={0, 1, -1, 0, 0}, yy[]={0, 0, 0, 1, -1};
bool inline NotOut(int, int);
int inline Find(int);
void inline Union(int, int);
bool inline Check_And_Union(P, int);
int col[N][N];
int fa[N*N];
int lf[N*N];
int num[N][N];
bool vis[N][N];
int n;
int main () {
    queue<P>black, white;
    read(n);
    char ch;
    int cnt=0;
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            cin>>ch;
            if (ch=='X') {
                col[i][j]=1;
            }else {
                if (ch=='O') {
                    col[i][j]=2;
                }else {
                    col[i][j]=0;
                }
            }
            num[i][j]=++cnt;
            fa[cnt]=cnt;
        }
    }
    for (int i=1; i<=n; ++i) {
        for (int j=1; j<=n; ++j) {
            if (!col[i][j]) {
                black.push(P(i, j));
                white.push(P(i, j));
            }else {
                for (int k=1; k<=4; ++k) {
                    int nx=i+xx[k], ny=j+yy[k];
                    if (NotOut(nx, ny)) {
                        if (!col[nx][ny]) {
                            ++lf[Find(num[i][j])];
                        }else {
                            if (col[i][j]==col[nx][ny]) {
                                Union(num[i][j], num[nx][ny]);
                            }
                        }
                    }
                }
            }
        }
    }
    while (true) {
        bool flag=true;
        while (!black.empty()) {
            P now=black.front();
            black.pop();
            if (Check_And_Union(now, 1)) {
                write(now.first);SP;write(now.second);EL;
                flag=false;
                break;
            }
        }
        if (flag) {
            break;
        }
        flag=true;
        while (!white.empty()) {
            P now=white.front();
            white.pop();
            if (Check_And_Union(now, 2)) {
                write(now.first);SP;write(now.second);EL;
                flag=false;
                break;
            }
        }
        if (flag) {
            break;
        }
    }
    write(-1);SP;write(-1);EL;
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
bool NotOut(int i, int j) {
    return i>=1&&j>=1&&i<=n&&j<=n;
}
int Find(int x) {
    if (fa[x]==x) {
        return x;
    }
    return fa[x]=Find(fa[x]);
}
void Union(int x, int y) {
    int fx=Find(x), fy=Find(y);
    if (fx^fy) {
        fa[fy]=fx;
        lf[fx]+=lf[fy];
    }
}
bool Check_And_Union(P a, int mod) {
    if (col[a.first][a.second]) {
        return false;
    }
    col[a.first][a.second]=mod;
    bool flag=true;
    int u=num[a.first][a.second];
    int now=0;
    for (int i=1; i<=4; ++i) {
        int nx=a.first+xx[i], ny=a.second+yy[i];
        if (NotOut(nx, ny)) {
            int v=Find(num[nx][ny]);
            if (!col[nx][ny]) {
                ++lf[u];
                ++now;
            }else {
                if (--lf[v]==0){
                    flag=false;
                    if (mod!=col[nx][ny]) {
                        now=-5;
                    }
                }
            }
        }
    }
    for (int i=1; i<=4; ++i) {
        int nx=a.first+xx[i], ny=a.second+yy[i];
        if (NotOut(nx, ny)) {
            int v=Find(num[nx][ny]);
            if (mod==col[nx][ny]) {
                now+=lf[v]>0;
            }
        }
    }
    if (now<=0) {
        flag=false;
    }
    if (flag||now>0) {
        for (int i=1; i<=4; ++i) {
            int nx=a.first+xx[i], ny=a.second+yy[i];
            if (NotOut(nx, ny)) {
                int v=Find(num[nx][ny]);
                if (mod==col[nx][ny]) {
                    Union(u, v);
                }
            }
        }
        return true;
    }
    for (int i=1; i<=4; ++i) {
        int nx=a.first+xx[i], ny=a.second+yy[i];
        if (NotOut(nx, ny)) {
            int v=Find(num[nx][ny]);
            if (col[nx][ny]) {
                ++lf[v];
            }else {
                --lf[u];
            }
        }
    }
    col[a.first][a.second]=0;
    return false;
}
