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
int step[1005];
int main(){
    for(int i=1;i<=1000;++i)step[i]=inf32;
    step[1]=0;
    for(int i=1;i<=1000;++i){
        if(step[i]==inf32)continue;
        for(int j=1;j<=i;++j){
            int v=i+i/j;
            if(v<=1000){
                step[v]=min(step[v],step[i]+1);
            }
        }
    }
    int t=read();
    while(t--){
        int N=read(),K=read();
        K=min(K,13*N);
        vector<int>b(N+1),c(N+1);
        for(int i=1;i<=N;++i)b[i]=read();
        for(int i=1;i<=N;++i)c[i]=read();
        vector<vector<int>>dp(N+5,vector<int>(K+5,-inf32));
        dp[0][0]=0;
        for(int i=1;i<=N;++i){
            for(int j=0;j<=K;++j){
                dp[i][j]=max(dp[i][j],dp[i-1][j]);
                int pj=j-step[b[i]];
                if(pj>=0){
                    dp[i][j]=max(dp[i][j],dp[i-1][pj]+c[i]);
                }
                //printf("dp[%d][%d]=%d\n",i,j,dp[i][j]);
            }
        }
        int ans=0;
        for(int i=0;i<=K;++i){
            ans=max(ans,dp[N][i]);
        }
        printf("%d\n",ans);
    }
}