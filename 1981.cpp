#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
long long a[100005];
const int Mod=10000;
bool number(char c);
int main(){
    string s;
    long long n,m=0,now,i,k=0,ans=0;
    bool flag=0;
    cin>>s;
    n=s.size();
    s[n]='+';
    now=0;
    for(i=0;i<=n;i++){
        if(number(s[i])){
            now=now*10+s[i]-'0';
        }else{
            if(s[i]=='*'){
                if(flag){
                    k*=now%Mod;
                    k%=Mod;
                }else{
                    k=now%Mod;
                }
                flag=1;
            }else{
                if(flag){
                    k*=now%Mod;
                    k%=Mod;
                    a[++m]=k;
                }else{
                    a[++m]=now%Mod;
                }
                flag=0;
            }
            now=0;
        }
    }
    for(i=1;i<=m;i++){
        ans+=a[i];
        ans%=Mod;
    }
    cout<<ans<<endl;
}
bool number(char c){
    if(c>='0'&&c<='9'){
        return true;
    }
    return false;
}
