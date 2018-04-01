#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<deque>
using namespace std;
deque<int>a;
int main(){
	int n,m,i,j,k=0;
	char b,d;
	cin>>n;
	for(i=1;i<=n;i++){
		cin>>b>>d;
		if(b=='A'){
			if(d=='L'){
				a.push_front(++k);
			}else{
				a.push_back(++k);
			}
		}else{
			cin>>m;
			for(j=1;j<=m;j++){
				if(d=='L'){
					a.pop_front();
				}else{
					a.pop_back();
				}
			}
		}
	}
	while(!a.empty()){
		cout<<a.front()<<endl;
		a.pop_front();
	}
	return 0;
}
