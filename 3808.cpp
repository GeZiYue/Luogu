#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar(' ')
#define EL putchar('\n')
#define N 500005
#define CTI(a) ((a)-'a'+1)
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
template<class T1>void read(T1 &r_e_a_d);
template<class T1>void write(T1 w_r_i_t_e);
class Tree_Char{
public:
    int fail;
    int end;
    int vis[30];
};
class Trie{
private:
    queue<int>q;
    Tree_Char P[N];
    int id;
public:
    Trie(){
        id=0;
    }
    void Add(string);
    void Build();
    int Find(string);
}AC;
int main(){
    int n,i;
    string str;
    read(n);
    for(i=1;i<=n;i++){
        cin>>str;
        AC.Add(str);
    }
    AC.Build();
    cin>>str;
    write(AC.Find(str));
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
void Trie::Add(string str){
    int i,len=str.size(),now=0;
    for(i=0;i<len;i++){
        if(P[now].vis[CTI(str[i])]==0){
            P[now].vis[CTI(str[i])]=++id;
        }
        now=P[now].vis[CTI(str[i])];
    }
    P[now].end++;
}
void Trie::Build(){
    int i,now;
    for(i=1;i<=26;i++){
        if(P[0].vis[i]!=0){
            P[P[0].vis[i]].fail=0;
            q.push(P[0].vis[i]);
        }
    }
    while(!q.empty()){
        now=q.front();
        q.pop();
        for(i=1;i<=26;i++){
            if(P[now].vis[i]!=0){
                P[P[now].vis[i]].fail=P[P[now].fail].vis[i];
                q.push(P[now].vis[i]);
            }else{
                P[now].vis[i]=P[P[now].fail].vis[i];
            }
        }
    }
}
int Trie::Find(string str){
    int i,j,now=0,len=str.size(),ans=0;
    for(i=0;i<len;i++){
        now=P[now].vis[CTI(str[i])];
        for(j=now;j&&P[j].end!=-1;j=P[j].fail){
            ans+=P[j].end;
            P[j].end=-1;
        }
    }
    return ans;
}
