#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 1005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
string str;
int a[N],b[N];
int main(){
    int n,m,i,len=0;
    read(m);
    cin>>str;
    n=str.size();
    for(i=n-1;i>=0;i--){
        if(str[i]!='0'){
            a[++len]=n-i-1;
            b[len]=str[i]-'0';
        }
    }
    for(i=len;i>=2;i--){
        write(b[i]);
        putchar('*');
        write(m);
        putchar('^');
        write(a[i]);
        putchar('+');
    }
    write(b[i]);
    putchar('*');
    write(m);
    putchar('^');
    write(a[i]);
    EL;
    return 0;
}
template<class T1>void read(T1 &r_e_a_d){
    T1 k=0;
    char ch=getchar();
    int flag=1;
    while(!isNum(ch)){
        if(ch=='-'){
            flag=-1;
        }
        ch=getchar();
    }
    while(isNum(ch)){
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    r_e_a_d=flag*k;
}
template<class T1>void write(T1 w_r_i_t_e){
    if(w_r_i_t_e<0){
        putchar('-');
        write(-w_r_i_t_e);
    }else{
        if(w_r_i_t_e<10){
            putchar(w_r_i_t_e+'0');
        }else{
            write(w_r_i_t_e/10);
            putchar((w_r_i_t_e%10)+'0');
        }
    }
}
