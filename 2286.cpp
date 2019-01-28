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
#define inf 1000000001
#define N 10005
#define Mod 1000000
#define File(a) freopen(a".in", "r", stdin), freopen(a".out", "w", stdout)
template<class T>inline void read(T&);
template<class T>inline void write(const T&);
class Splay {
private:
    class Node {
    public:
        int ch[2], fa;
        int v, rec;
        Node(int lc=0, int rc=0, int father=0, int value=0) {
            ch[0]=lc;
            ch[1]=rc;
            fa=father;
            v=value;
        }
    };
    Node *T;
    int root, cnt;
public:
    Splay() {
        root=0;
        T=new Node[N];
    }
    ~Splay() {
        delete[] T;
    }
    bool getid(int);
    void connect(int, int, bool);
    void rotate(int);
    void splay(int, int);
    void insert(int);
    int lower(int);
    int upper(int);
    void del(int);
    void erase(int);
}S;
int main () {
    int typ=1;
    int sum=0;
    int res=0;
    int n;
    read(n);
    for (int i=1; i<=n; ++i) {
        int a, b;
        read(a);
        read(b);
        if (a==0) {
            a=-1;
        }
        if (a==typ) {
            S.insert(b);
            ++sum;
        }else {
            if (sum==0) {
                S.insert(b);
                typ=-typ;
                sum=1;
                continue;
            }
            int ans;
            int x=S.lower(b);
            int y=S.upper(b);
            if (x==-inf) {
                ans=y-b;
                S.erase(y);
            }else {
                if (y==inf) {
                    ans=b-x;
                    S.erase(x);
                }else {
                    if (y-b<b-x) {
                        ans=y-b;
                        S.erase(y);
                    }else {
                        ans=b-x;
                        S.erase(x);
                    }
                }
            }
            res=(res*1ll+ans)%Mod;
            --sum;
        }
    }
    write(res);
    EL;
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
bool Splay::getid(int x) {
    return T[T[x].fa].ch[1]==x;
}
void Splay::connect(int x, int fa, bool how) {
    if (fa) {
        T[fa].ch[how]=x;
    }
    T[x].fa=fa;
}
void Splay::rotate(int x) {
    int y=T[x].fa;
    int R=T[y].fa;
    int yson=getid(x);
    int Rson=getid(y);
    connect(T[x].ch[yson^1], y, yson);
    connect(y, x, yson^1);
    connect(x, R, Rson);
}
void Splay::splay(int x, int to) {
    to=T[to].fa;
    while (T[x].fa!=to) {
        if (T[T[x].fa].fa==to) {
            rotate(x);
        }else {
            if (getid(x)==getid(T[x].fa)) {
                rotate(T[x].fa), rotate(x);
            }else {
                rotate(x), rotate(x);
            }
        }
    }
    if (!to) {
        root=x;
    }
}
void Splay::insert(int t) {
    if (root==0) {
        root=++cnt;
        T[1].v=t;
        T[1].rec=1;
        return;
    }
    int now=root;
    while (true) {
        if (T[now].v==t) {
            ++T[now].rec;
            splay(now, root);
            return;
        }
        bool nxt=T[now].v<t;
        if (T[now].ch[nxt]==0) {
            T[++cnt].v=t;
            T[cnt].rec=1;
            connect(cnt, now, nxt);
            splay(cnt, root);
            return;
        }else {
            now=T[now].ch[nxt];
        }
    }
}
int Splay::lower(int t) {
    int now=root;
    int maxi=-inf;
    while (true) {
        if (T[now].v<t) {
            maxi=max(maxi, T[now].v);
        }
        bool nxt=T[now].v<t;
        if (!T[now].ch[nxt]) {
            break;
        }
        now=T[now].ch[nxt];
    }
    splay(now, root);
    return maxi;
}
int Splay::upper(int t) {
    int now=root;
    int mini=inf;
    while (true) {
        if (T[now].v>t) {
            mini=min(mini, T[now].v);
        }
        bool nxt=T[now].v<=t;
        if (!T[now].ch[nxt]) {
            break;
        }
        now=T[now].ch[nxt];
    }
    splay(now, root);
    return mini;
}
void Splay::erase(int t) {
    int now=root;
    while (true) {
        if (T[now].v==t) {
            if (T[now].rec>1) {
                --T[now].rec;
                splay(now, root);
            }
            if (!T[now].ch[0]&&!T[now].ch[1]) {
                T[T[now].fa].ch[getid(now)]=0;
                if (now==root) {
                    root=0;
                    cnt=0;
                    memset(T, 0, sizeof(Node)*(N-1));
                }
            }else {
                if (!T[now].ch[0]) {
                    if (now==root) {
                        root=T[now].ch[1];
                    }
                    connect(T[now].ch[1], T[now].fa, getid(now));
                }else {
                    if (!T[now].ch[1]) {
                        if (now==root) {
                            root=T[now].ch[0];
                        }
                        connect(T[now].ch[0], T[now].fa, getid(now));
                    }else {
                        int left=T[now].ch[0];
                        while (T[left].ch[1]) {
                            left=T[left].ch[1];
                        }
                        splay(left, T[now].ch[0]);
                        connect(T[now].ch[1], left, 1);
                        connect(left, T[now].fa, getid(now));
                        if (now==root) {
                            root=left;
                        }
                        splay(left, root);
                    }
                }
            }
            return;
        }else {
            bool nxt=T[now].v<t;
            if (!T[now].ch[nxt]) {
                break;
            }else {
                now=T[now].ch[nxt];
            }
        }
    }
}
