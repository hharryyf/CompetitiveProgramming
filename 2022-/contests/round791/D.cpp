#pragma GCC optimize(3)
#pragma GCC optimize(2)
//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <set>
#include <queue>
#include <cassert>
#include <cmath>
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
//mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
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
ll MM;
int N,M,a[200005];
ll K;
vector<int>g[200005];
vector<int>g2[200005];
vector<int>st;
int low[200005],dfn[200005],instack[200005],cnt,dp[200005];
int hascycle;
void tarjan(int v){
    st.push_back(v);
    instack[v]=1;
    dfn[v]=low[v]=++cnt;
    for(int nv:g2[v]){
        if(dfn[nv]==-1){
            tarjan(nv);
            low[v]=min(low[v],low[nv]);
        }
        else if(instack[nv]){
            low[v]=min(low[v],dfn[nv]);
        }
    }
    if(low[v]==dfn[v]){
        vector<int>tmp;
        while(st.back()!=v){
            int u=st.back();
            tmp.push_back(u);
            st.pop_back();
            instack[u]=0;
        }
        instack[st.back()]=0;
        tmp.push_back(st.back());
        st.pop_back();
        if(tmp.size()>1){
            hascycle=1;
        }
    }
}
void DFS(int v){
    if(dp[v]!=-1){
        return;
    }
    dp[v]=1;
    for(int nv:g2[v]){
        if(dp[nv]==-1){
            DFS(nv);
        }
        dp[v]=max(dp[v],dp[nv]+1);
    }
}
bool check(ll m){
    MM=m;
    hascycle=0;
    st.clear();
    for(int i=1;i<=N;++i){
        g2[i].clear();
        dfn[i]=-1;
        instack[i]=0;
        low[i]=-1;
    }
    for(int i=1;i<=N;++i){
        for(int j:g[i]){
            if(a[i]<=m&&a[j]<=m){
                g2[i].push_back(j);
            }
        }
    }
    cnt=0;
    for(int i=1;i<=N;++i){
        if(a[i]<=m&&dfn[i]==-1)tarjan(i);
    }
    if(hascycle)return true;
    for(int i=1;i<=N;++i){
        dp[i]=-1;
    }
    for(int i=1;i<=N;++i){
        if(a[i]<=m){
            DFS(i);
        }
    }
    for(int i=1;i<=N;++i){
        if(a[i]<=m&&dp[i]>=K){
            return true;
        }
    }
    return false;
}
int main(){
    N=read();
    M=read();
    K=read();
    for(int i=1;i<=N;++i){
        a[i]=read();
    }
    for(int i=1;i<=M;++i){
        int u=read();
        int v=read();
        g[u].push_back(v);
    }
    ll l=0,r=1e9+10,ans=r;
    while(l<=r){
        ll mid=(l+r)/2;
        if(check(mid)){
            ans=mid;
            r=mid-1;
        }
        else{
            l=mid+1;
        }
    }
    if(ans==1e9+10){
        printf("-1\n");
    }
    else{
        printf("%lld\n",ans);
    }
}   