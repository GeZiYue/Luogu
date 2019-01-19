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
#define N 1005
#define M 505
#define Mod 100000000
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
class BigInteger {
private:
    int Int[M];
    int len;
    void AddLen(const int& k) {
        len+=k;
    }
public:
    int& operator[](const int&);
    BigInteger operator+(const BigInteger&);
    BigInteger operator*(const int&);
    BigInteger operator/(const int&);
    bool operator>(const BigInteger&)const;
    void Write();
    BigInteger() {
        len=0;
        memset(Int, 0, sizeof(Int));
    }
    BigInteger(int k) {
        len=0;
        memset(Int, 0, sizeof(Int));
        while (k) {
            Int[++len]=k%Mod;
            k/=Mod;
        }
    }
};
BigInteger max(const BigInteger&, const BigInteger&);
BigInteger ans;
pair<int, int>A[N];
int main () {
    int n;
    read(n);
    for (int i=0; i<=n; ++i) {
        read(A[i].first);
        read(A[i].second);
    }
    sort(A+1, A+n+1, [](pair<int, int>i, pair<int, int>j) {
        return i.first*1ll*i.second<j.first*1ll*j.second;
    });
    BigInteger ans(0);
    BigInteger now(1);
    for (int i=1; i<=n; ++i) {
        now=now*A[i-1].first;
        ans=max(ans, now/A[i].second);
    }
    ans.Write();
    EL;
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
template<class Fir, class... Res>void read(Fir& Fi, Res&... Re) {
    read(Fi);
    read(Re...);
}
template<class T>void write(const T& Wr) {
    if (Wr<0) {
        putchar('-');
        write(-Wr);
    }else {
        if (Wr<10) {
            putchar(floor(Wr)+'0');
        }else {
            write(Wr/10);
            putchar(Wr-10*floor(Wr/10)+'0');
        }
    }
}
template<class Fir, class... Res>void write(const Fir& Fi, const Res&... Re) {
    write(Fi);
    putchar(' ');
    write(Re...);
}
int& BigInteger::operator[](const int& k) {
    return Int[k];
}
BigInteger BigInteger::operator+(const BigInteger& k) {
    ans=BigInteger(0);
    ans.AddLen(max(len, k.len));
    int num=0;
    for (int i=1; i<=max(len, k.len); ++i) {
        ans[i]=Int[i]+k.Int[i]+num;
        num=ans[i]/Mod;
        ans[i]%=Mod;
    }
    if (num) {
        ans.AddLen(1);
        ans[ans.len]=1;
    }
    return ans;
}
BigInteger BigInteger::operator*(const int& k) {
    ans=BigInteger(*this);
    int num=0;
    long long int tmp;
    for (int i=1; i<=ans.len; ++i) {
        tmp=ans[i];
        tmp*=k;
        tmp+=num;
        num=tmp/Mod;
        tmp%=Mod;
        ans[i]=tmp;
    }
    while (num) {
        ans.AddLen(1);
        ans[ans.len]=num%Mod;
        num/=Mod;
    }
    return ans;
}
BigInteger BigInteger::operator/(const int& k) {
    long long int now=0;
    ans=BigInteger(0);
    for (int i=len; i>=1; --i) {
        now=now*1ll*Mod+Int[i];
        ans=ans*Mod+now/k;
        now%=k;
    }
    return ans;
}
bool BigInteger::operator>(const BigInteger& k)const {
    if (len>k.len) {
        return true;
    }else {
        if (len<k.len) {
            return false;
        }
    }
    for (int i=len; i>=1; --i) {
        if (Int[i]>k.Int[i]) {
            return true;
        }else {
            if (Int[i]<k.Int[i]) {
                return false;
            }
        }
    }
    return false;
}
void BigInteger::Write() {
    printf("%d", Int[len]);
    for (int i=len-1; i>=1; --i) {
        printf("%08d", Int[i]);
    }
}
BigInteger max(const BigInteger& a, const BigInteger& b) {
    if (a>b) {
        return a;
    }
    return b;
}
