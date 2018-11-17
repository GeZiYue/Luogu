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
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define N 105
#define M 4505
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
bool f[N][N];
int win[N], lose[N];
queue<int>q;
int main () {
	int n, m;
	read(n);
	read(m);
	for (int i=1; i<=m; ++i) {
		int x, y;
		read(x);
		read(y);
		f[x][y]=true;
	}
	for (int k=1; k<=n; ++k) {
		for (int i=1; i<=n; ++i) {
			if (i==k) {
				continue;
			}
			for (int j=1; j<=n; ++j) {
				if (j==i||j==k) {
					continue;
				}
				f[i][j]|=f[i][k]&f[k][j];
			}
		}
	}
	int ans=0;
	for (int i=1; i<=n; ++i) {
		for (int j=1; j<=n; ++j) {
			if (i==j) {
				continue;
			}
			win[i]+=f[i][j];
			lose[i]+=f[j][i];
		}
		if (win[i]+lose[i]==n-1) {
			++ans;
		}
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
