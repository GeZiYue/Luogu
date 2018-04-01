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
#define N 3000000
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int que_Max[N],que_Min[N];
int qh_Max,qt_Max,qh_Min,qt_Min;
int a[N];
int main(){
    int n,k,i,ans=0,now;
    read(k);
    read(n);
    for(i=1;i<=n;i++){
        read(a[i]);
    }
    que_Max[1]=que_Min[1]=qh_Max=qt_Max=qh_Min=qt_Min=1;
    for(i=2;i<=n;i++){
        while(qh_Max<=qt_Max&&a[que_Max[qt_Max]]<a[i]){
            qt_Max--;
        }
        que_Max[++qt_Max]=i;
        while(qh_Min<=qt_Min&&a[que_Min[qt_Min]]>a[i]){
            qt_Min--;
        }
        que_Min[++qt_Min]=i;
        while(a[que_Max[qh_Max]]-a[que_Min[qh_Min]]>k){
            if(que_Max[qh_Max]<que_Min[qh_Min]){
                now=que_Max[qh_Max];
                qh_Max++;
            }else{
                now=que_Min[qh_Min];
                qh_Min++;
            }
        }
        ans=max(ans,i-now);
    }
    write(ans);
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
