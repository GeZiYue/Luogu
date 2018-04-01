#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
int main(){
	int n,k,i,j,num=0;
	string s;
	cin>>s>>k;
	while(k--){
		n=s.size()-1;
		for(i=0;i<n;i++){
			if(s[i]>s[i+1]){
				s.erase(i,1);
				goto br;
			}
		}
		s.erase(n,1);
		br:;
	}
	n=s.size();
	while(s[0]=='0'){
		s.erase(0,1);
	}
	if(s.empty()){
		cout<<0<<endl;
		return 0;
	}
	cout<<s<<endl;
	return 0;
}

