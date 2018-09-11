#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
using namespace std;
#define isNum(a) (a >= '0' && a <= '9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define N 200005
#define File(a) freopen(a".in" , "r" , stdin) , freopen(a".out" , "w" , stdout)
template<class T1>void read(T1&);
template<class T1>void write(T1);
template<class T1 , class T2=less<T1> >
	class Heap{
	private:
		typedef size_t size_type;
		vector<T1>H;
		T2 c_h_e_c_k;
	public:
		Heap() {
            H.reserve(10000005);
            H.resize(1);
		}
		size_type size() {
			return H.size() - 1;
		}
        bool empty() {
            return this->size() == 0;
        }
		T1 at(size_type n) {
			if (n > this->size()){
				throw("Error, too big");
			}else{
				return H.at(n);
			}
		}
        T1& operator [](size_type n) {
            return H[n];
        }
		void down(size_type n,size_type s) {
			size_type i = n , j = 2 * n;
			H[0] = H[i];
			while (j <= s) {
				if (j < s && c_h_e_c_k.operator()(H[j] , H[j+1])) {
					j++;
				}
				if (c_h_e_c_k.operator()(H[0] , H[j])) {
					H[i] = H[j];
					i = j;
					j *= 2;
				}else {
					break;
				}
			}
			H[i] = H[0];
		}
		void up(size_type n) {
			size_type i = n , j = n / 2;
			H[0] = H[i];
			while (j >= 1 && (!(c_h_e_c_k.operator()(H[0] , H[j])))) {
				H[i] = H[j];
				i /= 2;
				j /= 2;
			}
			H[i] = H[0];
		}
		void make() {
			size_type s = this->size();
			for(size_type i = s / 2 ; i >= 1 ; i--) {
				this->down(i , s);
			}
		}
		void sort() {
			size_type s = this->size();
			this->make();
			for(size_type i = 1 ; i <= s ; i++) {
				swap(H[s - i + 1] , H[1]);
				this->down(1 , size_type(s - i));
			}
		}
		void put(T1 n) {
            if (H.size() == 0) {
                H.push_back(n);
            }
			H.push_back(n);
		}
        void push(T1 n) {
            put(n);
            this->up(this->size());
        }
        void pop() {
			size_type s = this->size();
            if (s == 0) {
                return;
            }
            H[1] = H[s];
            H.pop_back();
            this->down(1 , s - 1);
        }
        T1 top() {
            size_type s = this->size();
            if (s == 0) {
                return -1;
            }
            return H[1];
        }
	};
Heap<int>h1;
Heap<int , greater<int> >h2;
int a[N];
int main () {
    int n , m , i , j , u;
    read(n);
    read(m);
    for (i = 1 ; i <= n ; i++) {
        read(a[i]);
    }
    j = 1;
    for (i = 1 ; i <= m ; i++) {
        read(u);
        while (j <= u) {
            h1.push(a[j]);
            j++;
            if (h1.size() == i) {
                h2.push(h1.top());
                h1.pop();
            }
        }
        write(h2.top());
        EL;
        h1.push(h2.top());
        h2.pop();
    }
    return 0;
}
template<class T1>void read(T1 &r_e_a_d) {
    T1 k = 0;
    char ch = getchar();
    int flag = 1;
    while(!isNum(ch) ) {
        if (ch == '-') {
            flag = -1;
        }
        ch = getchar();
    }
    while(isNum(ch) ) {
        k = (k << 1) + (k << 3) + ch - '0';
        ch = getchar();
    }
    r_e_a_d = flag * k;
}
template<class T1>void write(T1 w_r_i_t_e) {
    if (w_r_i_t_e < 0) {
        putchar('-');
        write(-w_r_i_t_e);
    }else {
        if (w_r_i_t_e < 10) {
            putchar(w_r_i_t_e + '0');
        }else {
            write(w_r_i_t_e / 10);
            putchar( (w_r_i_t_e % 10) + '0');
        }
    }
}
