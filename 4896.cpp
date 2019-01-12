#include<iostream>
#include<cstdio>
#include<cmath>
#include<string>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
#define isNum(a) (a>='0'&&a<='9')
#define SP putchar (' ')
#define EL putchar ('\n')
#define inf 2147483647
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class Fir, class... Res>void read(Fir&, Res&...);
template<class T>inline void write(const T&);
template<class Fir, class... Res>void write(const Fir&, const Res&...);
string A, B, C;
string a, b, c, d, e;
const string sp(" started playing games!");
const string ep(" stopped playing games!");
const string cm(" came!");
const string lf(" left!");
bool ba, bb, bc, bd, be;
bool ia, ib, ic, id, ie;
bool it;
int main () {
    int n;
    read(n);
    cin>>A>>B>>C>>a>>b>>c>>d>>e;
    getchar();
    for (int i=1; i<=n; ++i) {
        string str;
        getline(cin, str);
        str=string(str.c_str());
        int siz=str.size();
        if (siz<7) {
            continue;
        }
        if (str[siz-1]!='!') {
            continue;
        }
        if (str[siz-2]!='s') {
            goto beg1;
        }
        if (str==a+sp) {
            ba=true;
            if (it) {
                ia=true;
            }
        }else {
            if (str==b+sp) {
                bb=true;
                if (it) {
                    ib=true;
                }
            }else {
                if (str==c+sp) {
                    bc=true;
                    if (it) {
                        ic=true;
                    }
                }else {
                    if (str==d+sp) {
                        bd=true;
                        if (it) {
                            id=true;
                        }
                    }else {
                        if (str==e+sp) {
                            be=true;
                            if (it) {
                                ie=true;
                            }
                        }else {
                            if (str==a+ep) {
                                ba=false;
                            }else {
                                if (str==b+ep) {
                                    bb=false;
                                }else {
                                    if (str==c+ep) {
                                        bc=false;
                                    }else {
                                        if (str==d+ep) {
                                            bd=false;
                                        }else {
                                            if (str==e+ep) {
                                                be=false;
                                            }else {
                                                beg1:;
                                                if (str==A+cm||
                                                    str==B+cm||
                                                    str==C+cm) {
                                                    it=true;
                                                    if (ba) {
                                                        ia=true;
                                                    }
                                                    if (bb) {
                                                        ib=true;
                                                    }
                                                    if (bc) {
                                                        ic=true;
                                                    }
                                                    if (bd) {
                                                        id=true;
                                                    }
                                                    if (be) {
                                                        ie=true;
                                                    }
                                                }else {
                                                    if (str==A+lf||
                                                        str==B+lf||
                                                        str==C+lf) {
                                                        it=false;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vector<string>ans;
    if (ia) {
        ans.push_back(a);
    }
    if (ib) {
        ans.push_back(b);
    }
    if (ic) {
        ans.push_back(c);
    }
    if (id) {
        ans.push_back(d);
    }
    if (ie) {
        ans.push_back(e);
    }
    sort(ans.begin(), ans.end());
    for (unsigned i=0; i<ans.size(); ++i) {
        cout<<ans[i].c_str()<<' ';
    }
    if (ans.size()) {
        EL;
    }
    if (ia&&ib&&ic&&id&&ie) {
        puts("How Bad Oiers Are!");
    }
    if (!(ia||ib||ic||id||ie)) {
        puts("How Good Oiers Are!");
    }
    return 0;
}
template<class T>void read(T &Re) {
    T k=0;
    char ch=getchar();
    int flag=1;
    while (!isNum(ch)) {
        if (ch=='-') {
            flag=-1;
        }
        ch=getchar();
    }
    while (isNum(ch)) {
        k=(k<<1)+(k<<3)+ch-'0';
        ch=getchar();
    }
    Re=flag*k;
}
template<class Fir, class... Res>void read(Fir& Fi, Res&... Re) {
    read(Fi);
    read(Re...);
}
template<class T>void write(const T& Wr) {
    if (Wr<0) {
        putchar('-');
        write(-Wr);
    }else {
        if (Wr<10) {
            putchar(Wr+'0');
        }else {
            write(Wr/10);
            putchar((Wr%10)+'0');
        }
    }
}
template<class Fir, class... Res>void write(const Fir& Fi, const Res&... Re) {
    write(Fi);
    putchar(' ');
    write(Re...);
}
