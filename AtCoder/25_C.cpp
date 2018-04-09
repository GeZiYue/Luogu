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
#define File(a) freopen((string(a)+string(".in")).c_str(),"r",stdin),freopen((string(a)+string(".out")).c_str(),"w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
bool check();
string str,now;
int main(){
    int i,j,n,maxn=0;
    cin>>str;
    n=str.size();
    for(i=1;i<(1<<n);i++){
        now.clear();
        for(j=0;j<n;j++){
            if((i>>j)&1){
                now+=str[j];
            }
        }
        if(check()){
            maxn=max(maxn,int(now.size()));
        }
    }
    write(maxn);
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
bool check(){
    int n=now.size();
    int i;
    for(i=0;i*2<n;i++){
        if((now[i]=='i'||now[i]=='w')&&(now[i]!=now[n-i-1])){
            return false;
        }
        if((now[i]=='('&&now[n-i-1]!=')')||(now[i]==')'&&now[n-i-1]!='(')){
            return false;
        }
        if((now[i]=='['&&now[n-i-1]!=']')||(now[i]==']'&&now[n-i-1]!='[')){
            return false;
        }
        if((now[i]=='{'&&now[n-i-1]!='}')||(now[i]=='}'&&now[n-i-1]!='{')){
            return false;
        }
    }
    if((n&1)&&!((now[n>>1]=='w')||now[n>>1]=='i')){
        return false;
    }
    bool flag=false;
    for(i=0;i+3<=n;i++){
        if(now.substr(i,3)=="iwi"){
            if(flag){
                return false;
            }else{
                flag=true;
            }
        }
    }
    return flag;
}
