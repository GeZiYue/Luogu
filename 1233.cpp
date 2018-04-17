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
#define N 20005
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
int find(int x);
class Node{
public:
    int high,wide;
    friend bool operator<(Node,Node);
}a[N];
bool flag[N];
int main(){
    int n,i,j,ans,noww;
    read(n);
    ans=n;
    for(i=1;i<=n;i++){
        read(a[i].high);
        read(a[i].wide);
    }
    sort(a+1,a+n+1);
    for(i=1;i<=n;i++){
        if(flag[i]){
            continue;
        }
        flag[i]=1;
        noww=a[i].wide;
        for(j=i+1;j<=n;j++){
            if(flag[j]){
                continue;
            }
            if(noww>=a[j].wide){
                noww=a[j].wide;
                flag[j]=1;
                ans--;
            }
        }
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
bool operator<(Node i,Node j){
    if(i.high==j.high){
        return i.wide>j.wide;
    }else{
        return i.high>j.high;
    }
}
