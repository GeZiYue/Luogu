#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
    int n;
    cin>>n;
    if((n%4==0&&n%100!=0)||(n%400==0)){
        cout<<"YES"<<endl;
    }else{
        cout<<"NO"<<endl;
    }
}
