#pragma GCC optimize(3)
#pragma GCC optimize(2)
#include <bits/stdc++.h>
#define x first
#define y second
#define debug if(0)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define FOR(i,a,b) for(int i=a;i<=b;++i)
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
    ll ans=x+y;
    if(ans>=mod){
        ans-=mod;
    }
    return ans;
    //return ((x+y)%mod+mod)%mod;
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
vector<int>g[200005];
int L[200005],R[200005],a[200005];
int N;
int ans;
ll solve(int v){
    if(g[v].size()==0){
        ++ans;
        return R[v]; 
    }
    vector<ll>bound;
    for(int nv:g[v]){
        bound.push_back(solve(nv));
    }
    ll sum=0;
    for(ll i:bound)sum+=i;
    if(sum>=L[v]){
        return min(sum,(ll)R[v]);
    }
    ++ans;
    return R[v];
}
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        for(int i=1;i<=N;++i)g[i].clear(),a[i]=0,L[i]=0,R[i]=0;
        for(int i=2;i<=N;++i){
            int p;
            cin>>p;
            g[p].push_back(i);
        }
        for(int i=1;i<=N;++i){
            cin>>L[i]>>R[i];
        }
        ans=0;
        solve(1);
        cout<<ans<<endl;
    }
}   