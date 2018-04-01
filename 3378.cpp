#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;
#define Int(a) read(a)
#define in inline
in void read(int &r_e_a_d);
template<class T1,class T2=less<int> >
	class Heap{
	private:
		typedef size_t size_type;
		vector<T1>H;
        T2 Check;
	public:
		in Heap(){
			H.push_back(-1);
            H.reserve(10000005);
            H.resize(1);
		}
		in size_type size(){
			return H.size()-1;
		}
		in T1 at(size_type n){
			if(n>this->size()){
				cout<<"Wrong"<<endl;
				exit(-1);
			}else{
				return H.at(n);
			}
		}
        in T1& operator [](size_type n){
            return H[n];
        }
		in void down(size_type n,size_type s){
			size_type i=n,j=2*n;
			H[0]=H[i];
			while(j<=s){
				if(j<s&&Check.operator()(H[j+1],H[j])){
					j++;
				}
				if(Check.operator()(H[j],H[0])){
					H[i]=H[j];
					i=j;
					j*=2;
				}else{
					break;
				}
			}
			H[i]=H[0];
		}
		in void up(size_type n){
			size_type i=n,j=n/2;
			H[0]=H[i];
			while(j>=1&&Check.operator()(H[0],H[j])){
				H[i]=H[j];
				i/=2;
				j/=2;
			}
			H[i]=H[0];
		}
		in void make(){
			size_type s=this->size();
			for(size_type i=s/2;i>=1;i--){
				this->down(i,s);
			}
		}
		in void sort(){
			size_type s=this->size();
			this->make();
			for(size_type i=1;i<=s;i++){
				swap(H[s-i+1],H[1]);
				this->down(1,size_type(s-i));
			}
		}
		in void put(T1 n){
			H.push_back(n);
		}
        in void push(T1 n){
            H.push_back(n);
            this->up(this->size());
        }
        in void pop(){
			size_type s=this->size();
            H[1]=H[s];
            H.pop_back();
            this->down(1,s-1);
        }
        in T1 top(){
            if(this->size()>=1){
                return H[1];
            }
        }
	};
int main(){
	int n,i,a;
	Heap<int>H;
    Int(n);
    for(i=1;i<=n;i++){
        Int(a);
        if(a==1){
            Int(a);
            H.push(a);
        }else{
            if(a==2){
                printf("%d\n",H.top());
            }else{
                H.pop();
            }
        }
    }
    return 0;
}
void read(int &r_e_a_d){
    int k=0;
    bool flag=0;
    char c;
    while(1){
        c=getchar();
        if(c=='-'){
            flag=1;
            break;
        }
        if(c>='0'&&c<='9'){
            k=c-'0';
            break;
        }
    }
    while(1){
        c=getchar();
        if(c<'0'||c>'9'){
            break;
        }else{
            k=(k<<1)+(k<<3)+c-'0';
        }
    }
    if(flag==1){
        k=-k;
    }
    r_e_a_d=k;
}
