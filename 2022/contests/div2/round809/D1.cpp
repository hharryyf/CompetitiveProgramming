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
const int maxn = 2e5 + 100;
const int inf32 = 1e9 + 5;
const ll inf64 = 1e18 + 10;
const ll mod=998244353;
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
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    int t;
    cin>>t;
    while(t--){
        int N,K;
        cin>>N>>K;
        vector<int>a(N+10);
        for(int i=1;i<=N;++i)cin>>a[i];
        vector<vector<int>>vec(N+10,vector<int>());
        vector<bool>present(3050);
        for(int i=1;i<=N;++i){
            for(int j=1;j<=K&&j<=a[i];++j){
                vec[i].push_back(a[i]/j);
                present[a[i]/j]=true;
            }
            sort(vec[i].begin(),vec[i].end());
        }
        int ans=inf32;
        for(int mv=0;mv<=3000;++mv){
            if(present[mv]==false)continue;
            int max_val=-1;
            int ok=1;
            for(int i=1;i<=N;++i){
                if(vec[i].back()<mv)ok=0;
                int l=0,r=vec[i].size()-1,index=-1;
                while(l<=r){
                    int mid=(l+r)/2;
                    if(vec[i][mid]>=mv){
                        index=mid;
                        r=mid-1;
                    }
                    else{
                        l=mid+1;
                    }
                }
                if(index>-1){
                    max_val=max(max_val,vec[i][index]);
                }
            }
            if(max_val>=mv&&ok){
                ans=min(ans,max_val-mv);
            }
        }
        cout<<ans<<endl;
    }
}   