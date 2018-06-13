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
#define N 1000005
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int ch(int );
int t[N],a[N];
int main(){
    int x,y,len=0,now=0,i,l=0;
    read(x);
    read(y);
    write(x/y);
    if(x/y==0){
        l=1;
    }
    l+=ch(x/y)+1;
    putchar('.');
    if(x%y==0){
        write(0);
    }
    x%=y;
    while(x){
        x*=10;
        if(t[x]){
            now=t[x];
            break;
        }
        a[++len]=x/y;
        t[x]=len;
        x%=y;
    }
    if(now==0){
        for(i=1;i<=len;i++){
            write(a[i]);
            l++;
            if(l==76){
                l=0;
                EL;
            }
        }
    }else{
        for(i=1;i<now;i++){
            write(a[i]);
            l++;
            if(l==76){
                l=0;
                EL;
            }
        }
        putchar('(');
        l++;
        if(l==76){
            l=0;
            EL;
        }
        for(i=now;i<=len;i++){
            write(a[i]);
            l++;
            if(l==76){
                l=0;
                EL;
            }
        }
        putchar(')');
    }
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
int ch(int x){
    int l=0;
    while(x){
        x/=10;
        l++;
    }
    return l;
}
