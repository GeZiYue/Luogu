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
#define N 1505
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
typedef pair<int, int> P;
bool DFS(int, int, int, int);
const int xx[]={0, 0, 0, 1, -1}, yy[]={0, 1, -1, 0, 0};
bool a[N][N];
P vis[N][N];
int n, m;
int main () {
    while (cin>>n>>m) {
        memset(a, 0, sizeof(a));
        memset(vis, false, sizeof(vis));
        int bx, by;
        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=m; ++j) {
                char ch;
                cin>>ch;
                if (ch=='#') {
                    a[i][j]=true;
                }else {
                    if (ch=='S') {
                        bx=i, by=j;
                    }
                }
            }
        }
        puts(DFS(bx, by, 1, 1)?"Yes":"No");
    }
    return 0;
}
template<class T>void read(T &Re) {
    T k=0;
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
    Re=flag*k;
}
template<class T>void write(const T& Wr) {
    if (Wr<0) {
        putchar('-');
        write(-Wr);
    }else {
        if (Wr<10) {
            putchar(Wr+'0');
        }else {
            write(Wr/10);
            putchar((Wr%10)+'0');
        }
    }
}
bool DFS(int x, int y, int idx, int idy) {
    if (vis[x][y]!=P(0, 0)) {
        return true;
    }
    vis[x][y]=P(idx, idy);
    for (int k=1; k<=4; ++k) {
        int nx=x+xx[k], ny=y+yy[k];
        int nix=idx, niy=idy;
        if (nx>n) {
            nx-=n;
            ++nix;
        }
        if (ny>m) {
            ny-=m;
            ++niy;
        }
        if (nx<1) {
            nx+=n;
            --nix;
        }
        if (ny<1) {
            ny+=m;
            --niy;
        }
        if (a[nx][ny]||vis[nx][ny]==P(nix, niy)) {
            continue;
        }
        if (DFS(nx, ny, nix, niy)) {
            return true;
        }
    }
    return false;
}
