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
#define N 270005
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
class Complex {
private:
    double Re, Im;
public:
    Complex(double Re=0, double Im=0):Re(Re), Im(Im) {}
    friend Complex operator+(const Complex&, const Complex&);
    friend Complex operator-(const Complex&, const Complex&);
    friend Complex operator*(const Complex&, const Complex&);
    friend Complex operator+=(Complex&, const Complex&);
    friend Complex operator-=(Complex&, const Complex&);
    friend Complex operator*=(Complex&, const Complex&);
    operator double() {
        return Re;
    }
}A[N], B[N];
void FFT(Complex*, int);
const double PI=acos(-1);
int R[N];
int L, l;
int ans[N];
int main () {
    int n;
    read(n);
    --n;
    for (int i=n; i>=0; --i) {
        char ch;
        cin>>ch;
        A[i]=Complex(ch-'0');
    }
    for (int i=n; i>=0; --i) {
        char ch;
        cin>>ch;
        B[i]=Complex(ch-'0');
    }
    for (L=1; L<=n<<1; ++l, L<<=1) ;
    for (int i=0; i<L; ++i) {
        R[i]=(R[i>>1]>>1)|((i&1)<<(l-1));
    }
    FFT(A, 1), FFT(B, 1);
    for (int i=0; i<=L; ++i) {
        A[i]*=B[i];
    }
    FFT(A, -1);
    int num=0;
    for (int i=0; i<=L; ++i) {
        ans[i]=int((double(A[i])/L+0.5))+num;
        num=ans[i]/10;
        ans[i]%=10;
    }
    while (!ans[L]) {
        --L;
    }
    while(num) {
        ans[L]=num;
        num=ans[L]/10;
        ans[L]%=10;
    }
    for (int i=L; i>=0; --i) {
        write(ans[i]);
    }
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
Complex operator+(const Complex& i, const Complex& j) {
    return Complex(i.Re+j.Re, i.Im+j.Im);
}
Complex operator-(const Complex& i, const Complex& j) {
    return Complex(i.Re-j.Re, i.Im-j.Im);
}
Complex operator*(const Complex& i, const Complex& j) {
    return Complex(i.Re*j.Re-i.Im*j.Im, i.Re*j.Im+i.Im*j.Re);
}
Complex operator+=(Complex& i, const Complex& j) {
    return i=Complex(i.Re+j.Re, i.Im+j.Im);
}
Complex operator-=(Complex& i, const Complex& j) {
    return i=Complex(i.Re-j.Re, i.Im-j.Im);
}
Complex operator*=(Complex& i, const Complex& j) {
    return i=Complex(i.Re*j.Re-i.Im*j.Im, i.Re*j.Im+i.Im*j.Re);
}
void FFT(Complex* a, int flag) {
    for (int i=0; i<L; ++i) {
        if (i<R[i]) {
            swap(a[i], a[R[i]]);
        }
    }
    for (int i=1; i<L; i<<=1) {
        Complex T(cos(PI/i), flag*sin(PI/i));
        for (int j=0; j<L; j+=(i<<1)) {
            Complex t(1);
            for (int k=0; k<i; ++k, t*=T) {
                Complex nx=a[j+k], ny=t*a[i+j+k];
                a[j+k]=nx+ny;
                a[i+j+k]=nx-ny;
            }
        }
    }
}
