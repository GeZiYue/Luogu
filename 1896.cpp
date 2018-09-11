#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 10
#define M 600
#define ll long long int
#define lowbit(x) (x & (-x))
#define File(a) freopen(a".in", "r", stdin) , freopen(a".out", "w", stdout)
template<class T1>inline void read(T1&);
template<class T1>inline void write(T1);
bool Check_Status(int);
int Count_Status(int);
void Make_Status();
bool Check_Two_Status(int, int);
int n, k;
int status[M], sum[M], id;
ll dp[N][M][N * N];
int main () {
    read(n);
    read(k);
    Make_Status();
    ll ans = 0;
    for (int i = 1; i <= id; i++) {
        dp[1][status[i]][sum[i]] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= id; j++) {
            for (int w = sum[j]; w <= min(i * n, k); w++) {
                for (int l = 1; l <= id; l++) {
                    if (Check_Two_Status(status[j], status[l])) {
                        continue;
                    }
                    dp[i][status[j]][w] += dp[i - 1][status[l]][w - sum[j]];
                }
                if (w == k && i == n) {
                    ans += dp[i][status[j]][w];
                }
            }
        }
    }
    write(ans);
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
bool Check_Status(int x) {
    while (x) {
        if ((x & 1) && ((x >> 1) & 1)) {
            return false;
        }
        x >>= 1;
    }
    return true;
}
int Count_Status(int x) {
    int ans = 0;
    while (x) {
        ans++;
        x -= lowbit(x);
    }
    return ans;
}
void Make_Status() {
    for (int i = 0; i < (1 << n); i++) {
        if (Check_Status(i) && Count_Status(i) <= k) {
            status[++id] = i;
            sum[id] = Count_Status(i);
        }
    }
}
bool Check_Two_Status(int x, int y) {
    int p = x;
    for (int i = 1; i <= n; i++) {
        if (x & (1 << (i - 1))) {
            if (i != 1) {
                p |= (1 << (i - 2));
            }
            if (i != n) {
                p |= (1 << i);
            }
        }
    }
    return (p & y);
}
