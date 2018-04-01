#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
#define Int(a) read(a)
#define Out(a) write(a)
#define mk(a,b) make_pair(a,b)
void read(int &r_e_a_d);
void write(int w_r_i_t_e);
pair<int,int>a[1000005],b[1000005];
int x[1000005];
int h1=1,h2=1,t1=0,t2=0;
int main(){
    int n,m,i,j,l;
    Int(n);
    Int(m);
    for(i=1;i<=n;i++){
        Int(x[i]);
        while(h1<=t1&&(i-a[h1].second)>=m){
            h1++;
        }
        while(h1<=t1&&a[t1].first>x[i]){
            t1--;
        }
        a[++t1]=mk(x[i],i);
        if(i>=m){
            Out(a[h1].first);
            putchar(' ');
        }
    }
    putchar('\n');
    for(i=1;i<=n;i++){
        while(h2<=t2&&(i-b[h2].second)>=m){
            h2++;
        }
        while(h2<=t2&&b[t2].first<x[i]){
            t2--;
        }
        b[++t2]=mk(x[i],i);
        if(i>=m){
            Out(b[h2].first);
            putchar(' ');
        }
    }
    putchar('\n');
    return 0;
}
void read(int &r_e_a_d){
    int k=0;
    bool flag=0;
    char c;
    while(1){
        c=getchar();
        if(c=='-'){
            flag=1;
            break;
        }
        if(c>='0'&&c<='9'){
            k=c-'0';
            break;
        }
    }
    while(1){
        c=getchar();
        if(c<'0'||c>'9'){
            break;
        }else{
            k=(k<<1)+(k<<3)+c-'0';
        }
    }
    if(flag==1){
        k=-k;
    }
    r_e_a_d=k;
}
void write(int w_r_i_t_e){
    if(w_r_i_t_e<0){
        putchar('-');
        write(-w_r_i_t_e);
        return;
    }
    if(w_r_i_t_e<10){
        putchar(w_r_i_t_e+'0');
        return;
    }else{
        write(w_r_i_t_e/10);
        putchar(w_r_i_t_e%10+'0');
        return;
    }
}