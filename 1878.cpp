#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define Int(a) read(a)
#define END printf("/n")
void read(int &r_e_a_d);
bool sex[200005];
int a[200005];
bool use[200005];
int out1[200005],out2[200005];
class cp;
template<class T1,class T2=less<T1> >
	class Heap{
	private:
		#define in inline
		typedef size_t size_type;
		vector<T1>H;
		T2 c_h_e_c_k;
	public:
		in Heap(){
			H.push_back(T1());
            H.reserve(10000005);
            H.resize(1);
		}
		in size_type size(){
			return H.size()-1;
		}
        in bool empty(){
            return this->size()==0;
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
				if(j<s&&c_h_e_c_k.operator()(H[j],H[j+1])){
					j++;
				}
				if(c_h_e_c_k.operator()(H[0],H[j])){
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
			while(j>=1&&(!(c_h_e_c_k.operator()(H[0],H[j])))){
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
            return H[1];
        }
	};
class cp{
public:
    int x1,x2,c;
    cp(int x,int y,int far):x1(x),x2(y),c(far){
    }
    cp():x1(0),x2(0),c(0){
	}
	bool operator()(cp &i,cp &j){
		if(i.c==j.c){
			return i.x1>j.x1;
		}else{
			return i.c>j.c;
		}
	}
};
Heap<cp,cp>K;
int main(){
    int n,i,ans=0;
    int l1,l2;
    int x,y;
    char c;
    Int(n);
    for(i=1;i<=n;i++){
        cin>>c;
        if(c=='B'){
            sex[i]=1;
        }else{
            sex[i]=0;
        }
    }
    for(i=1;i<=n;i++){
        Int(a[i]);
    }
    use[0]=use[n+1]=1;
    for(i=1;i<n;i++){
        if(sex[i]^sex[i+1]){
            K.push(cp(i,i+1,abs(a[i]-a[i+1])));
        }
    }
    while(!K.empty()){
		l1=K.top().x1;
		l2=K.top().x2;
    	use[l1]=use[l2]=1;
        out1[++ans]=x=l1;
        out2[ans]=y=l2;
        do{
        	K.pop();
        	l1=K.top().x1;
        	l2=K.top().x2;
		}while(!K.empty()&&(use[l1]||use[l2]));
        while(use[x]&&x>=1){
        	x--;
		}
		while(use[y]&&y<=n){
			y++;
		}
		if(x<1||y>n||(sex[x]==sex[y])){
			goto stop;
		}
		K.push(cp(x,y,abs(a[x]-a[y])));
		stop:;
    }
    cout<<ans;END;
    for(i=1;i<=ans;i++){
        cout<<out1[i]<<' '<<out2[i];END;
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
