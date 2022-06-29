#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define x first
#define y second
#define debug if(0)
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
const ll mod=1e9+7;
mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
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
int main(){
    int t=read();
    while(t--){
        int N=read();
        vector<ll>a(N),b(N);
        for(auto&i:a)i=read();
        for(auto&i:b)i=read();
        // 2 edges
        ll ans=min(abs(a[0]-b[0])+abs(a[N-1]-b[N-1]),abs(a[0]-b[N-1])+abs(a[N-1]-b[0]));
        // 3 edges
        ll cost=abs(a[0]-b[0]);
        ll ca=inf64,cb=inf64;
        for(ll i:b)ca=min(ca,abs(a[N-1]-i));
        for(ll i:a)cb=min(cb,abs(b[N-1]-i));
        ans=min(ans,cost+ca+cb);

        cost=abs(a[0]-b[N-1]);
        ca=inf64,cb=inf64;
        for(ll i:b)ca=min(ca,abs(a[N-1]-i));
        for(ll i:a)cb=min(cb,abs(b[0]-i));
        ans=min(ans,cost+ca+cb);

        cost=abs(a[N-1]-b[0]);
        ca=inf64,cb=inf64;
        for(ll i:b)ca=min(ca,abs(a[0]-i));
        for(ll i:a)cb=min(cb,abs(b[N-1]-i));
        ans=min(ans,cost+ca+cb);

        cost=abs(a[N-1]-b[N-1]);
        ca=inf64,cb=inf64;
        for(ll i:b)ca=min(ca,abs(a[0]-i));
        for(ll i:a)cb=min(cb,abs(b[0]-i));
        ans=min(ans,cost+ca+cb);
        // 4 edges
        ll c1=inf64,c2=inf64,c3=inf64,c4=inf64;
        for(ll i:a)c1=min(c1,abs(b[0]-i));
        for(ll i:a)c2=min(c2,abs(b[N-1]-i));
        for(ll i:b)c3=min(c3,abs(a[0]-i));
        for(ll i:b)c4=min(c4,abs(a[N-1]-i));
        ans=min(ans,c1+c2+c3+c4);
        printf("%lld\n",ans);
    }

    return 0;
}   