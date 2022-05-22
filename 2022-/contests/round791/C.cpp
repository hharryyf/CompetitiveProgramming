#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define x first
#define y second
#define debug if(0)
#define Brute if(0)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
using namespace std;
typedef long long ll;
typedef pair<ll , ll> pll;
typedef pair<int , int> pii;
typedef long double ld;
const int maxv = 1e6 + 10;
const int maxn = 5e5 + 10;
const int inf32 = 1e9 + 5;
const ll inf64 = 1e18 + 10;
const ll mod=998244353;
ll read(){
	bool minus=false;
	ll result=0;
	char ch;
	ch=getchar();
	while(true){
		if(ch=='-')break;
		if(ch>='0'&&ch<='9')break;
		ch=getchar();
	}
	if(ch == '-')minus=true;
    else result=ch-'0';
	while(true){
		ch=getchar();
		if(ch<'0'||ch>'9')break;
		result=result*10+(ch-'0');
	}
	if(minus)
		return -result;
	else
		return result;
}
inline ll add(ll x,ll y){
    return ((x+y)%mod+mod)%mod;
}
inline ll mul(ll x,ll y){
    return x*y%mod;
}
inline ll qpow(ll x,ll n){
    ll ret=1ll;
    while(n){
        if(n&1)ret=mul(ret,x);
        x=mul(x,x);
        n>>=1;
    }
    return ret;
}
ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}
ll lcm(ll n,ll m){
    return n*m/gcd(n,m);
}
int N,Q;
int R[100005],C[100005];
int row[100005*4],col[100005*4];
void add(int tree[], int pos,int v){
    while(pos<=N){
        tree[pos]+=v;
        pos+=pos&(-pos);
    }
}
int ask(int tree[], int pos){
    int ans=0;
    while(pos){
        ans+=tree[pos];
        pos-=pos&(-pos);
    }
    return ans;
}
void ADD(int r,int c){
    if(R[r]==0){
        add(row,r,1);
    }
    if(C[c]==0){
        add(col,c,1);
    }
    ++R[r];
    ++C[c];
}
void DEL(int r,int c){
    if(R[r]==1){
        add(row,r,-1);
    }
    if(C[c]==1){
        add(col,c,-1);
    }
    --R[r];
    --C[c];
}
int main(){
    N=read();
    Q=read();
    while(Q--){
        int t=read();
        if(t==1){
            int r=read();
            int c=read();
            // add
            ADD(r,c);
        }
        if(t==2){
            int r=read();
            int c=read();
            // remove
            DEL(r,c);            
        }
        if(t==3){
            int x1=read();
            int y1=read();
            int x2=read();
            int y2=read();
            if(ask(row,x2)-ask(row,x1-1)==x2-x1+1||ask(col,y2)-ask(col,y1-1)==y2-y1+1){
                printf("Yes\n");
            }
            else{
                printf("No\n");
            }
        }
    }
}   