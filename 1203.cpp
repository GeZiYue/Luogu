#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<fstream>
using namespace std;
char s[400];
int main(){
	int n,i,j,maxi=0,now;
	char k;
	cin>>n>>s+1;
	for(i=1;i<=n;i++){
		s[i+n]=s[i];
	}
	for(i=1;i<=n;i++){
		bool flag=0;
		bool t[400]={0};
		now=0;
		if(s[i]=='w'){
			flag=1;
		}else{
			k=s[i];
		}
		for(j=i;;j=(j==1?n:j-1)){
			if(flag==1){
				if(t[j]==1){
					break;
				}
				t[j]=1;
				if(s[j]!='w'){
					flag=0;
					k=s[j];
				}
				now++;
				continue;
			}
			if(s[j]==k||s[j]=='w'){
				if(t[j]==1){
					break;
				}
				t[j]=1;
				now++;
			}else{
				break;
			}
		}
		j=(i==n?1:i+1);
		if(t[j]==1){
			goto back;
		}
		flag=0;
		if(s[j]=='w'){
			flag=1;
		}else{
			k=s[j];
		}
		for(;;j=(j==n?1:j+1)){
			if(flag==1){
				if(t[j]==1){
					break;
				}
				t[j]=1;
				if(s[j]!='w'){
					flag=0;
					k=s[j];
				}
				now++;
				continue;
			}
			if(s[j]==k||s[j]=='w'){
				if(t[j]==1){
					break;
				}
				t[j]=1;
				now++;
			}else{
				break;
			}
		}
		back:;
		maxi=max(maxi,now);
	}
	cout<<maxi<<endl;
	return 0;
}

