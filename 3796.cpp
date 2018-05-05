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
class Trie{
public:
    int fail;
    int end;
    int ans;
    int vis[30];
};
class Aho_Corasick_automaton{
private:
    queue<int>q;
    Trie P[N];
    int maxn;
    int id;
public:
    Aho_Corasick_automaton(){
        id=0;
    }
    void Add(string,int);
    void Build();
    int Find(string);
    void Clear();
    void Out();
}AC;
class Str{
public:
    string str;
    int num,ans;
}a[200];
int main(){
    int n,i,maxn;
    string str;
    while(true){
        read(n);
        if(n==0){
            break;
        }
        AC.Clear();
        for(i=1;i<=n;i++){
            cin>>a[i].str;
            a[i].ans=0;
            AC.Add(a[i].str,a[i].num=i);
        }
        AC.Build();
        cin>>str;
        write(maxn=AC.Find(str));
        EL;
        for(i=1;i<=n;i++){
            if(a[i].ans==maxn){
                cout<<a[i].str<<endl;
            }
        }
    }
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
void Aho_Corasick_automaton::Add(string str,int num){
    int i,len=str.size(),now=0;
    for(i=0;i<len;i++){
        if(P[now].vis[CTI(str[i])]==0){
            P[now].vis[CTI(str[i])]=++id;
        }
        now=P[now].vis[CTI(str[i])];
    }
    P[now].end=num;
}
void Aho_Corasick_automaton::Build(){
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
int Aho_Corasick_automaton::Find(string str){
    int i,j,now=0,len=str.size();
    for(i=0;i<len;i++){
        now=P[now].vis[CTI(str[i])];
        for(j=now;j;j=P[j].fail){
            if(P[j].end!=0){
                a[P[j].end].ans++;
                maxn=max(maxn,a[P[j].end].ans);
            }
        }
    }
    return maxn;
}
void Aho_Corasick_automaton::Clear(){
    while(!q.empty()){
        q.pop();
    }
    int i;
    for(i=0;i<=id;i++){
        memset(P[i].vis,0,sizeof(P[i].vis));
        P[i].ans=P[i].end=P[i].fail=0;
    }
    id=0;
    maxn=0;
}
