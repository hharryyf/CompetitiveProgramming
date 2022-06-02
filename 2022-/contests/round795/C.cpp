// not my code, coded by Edward in practice contest
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
#include <map>
#include <unordered_map>
#include <random>
#include <unordered_set>
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
char a[100005];
int main(){
    int t=read();
    while(t--){
        int N=read();
        int K=read();
        scanf("%s",a+1);
        if(a[N]=='0')for(int i=N-1;i>=1;--i){
            if(a[i]=='1'){
                if(N-i<=K){
                    K-=N-i;
                    swap(a[i],a[N]);
                }
                break;
            }
        }
        for(int i=2;i<N;++i){
            if(a[i]=='1'){
                if(i-1<=K){
                    swap(a[i],a[1]);
                }
            }
        }
        int ans=0;
        for(int i=1;i<N;++i){
            int x=a[i]-'0';
            int y=a[i+1]-'0';
            ans+=x*10+y;
        }
        printf("%d\n",ans);
    }
}   