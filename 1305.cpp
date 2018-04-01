#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<map>
using namespace std;
map<char,char>l,r;
map<char,bool>t;
map<char,int>fin;
char s[30];
int head;
void gwork(int n);
int main(){
    int n,i;
    cin>>n;
    for(i=1;i<=n;i++){
        cin>>s[i];
        fin[s[i]]=i;
        cin>>l[s[i]];
        t[l[s[i]]]=1;
        cin>>r[s[i]];
        t[r[s[i]]]=1;
    }
    for(i=1;i<=n;i++){
        if(t[s[i]]==0){
            head=i;
            break;
        }
    }
    gwork(head);
    return 0;
}
void gwork(int n){
    cout<<s[n];
    if(l[s[n]]!='*'){
        gwork(fin[l[s[n]]]);
    }
    if(r[s[n]]!='*'){
        gwork(fin[r[s[n]]]);
    }
    return;
}
