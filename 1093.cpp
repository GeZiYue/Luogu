#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<fstream>
using namespace std;
class Student{
public:
	int Getc(){
		return a;
	}
	int Getm(){
		return b;
	}
	int Gete(){
		return c;
	}
	int Gets(){
		return sum;
	}
	int Getn(){
		return num;
	}
	void Putc(){
		cin>>a;
	}
	void Putm(){
		cin>>b;
	}
	void Pute(){
		cin>>c;
	}
	void Puts(){
		sum=a+b+c;
	}
	void Putn(int l){
		num=l;
	}
private:
	int a,b,c,num,sum;
}a[305];
bool cmp(Student x,Student y){
	if(x.Gets()==y.Gets()){
		if(x.Getc()==y.Getc()){
			return x.Getn()<y.Getn();
		}else{
			return x.Getc()>y.Getc();
		}
	}else{
		return x.Gets()>y.Gets();
	}
}
int main(){
	int n,i;
	cin>>n;
	for(i=1;i<=n;i++){
		a[i].Putc();
		a[i].Putm();
		a[i].Pute();
		a[i].Puts();
		a[i].Putn(i);
	}
	sort(a+1,a+n+1,cmp);
	for(i=1;i<=5;i++){
		cout<<a[i].Getn()<<' '<<a[i].Gets()<<endl;
	}
	return 0;
}

