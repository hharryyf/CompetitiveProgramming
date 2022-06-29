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
int main(){
    int t=read();
    while(t--){
        ll N=read();
        if(N&1||N<4){
            printf("-1\n");
            continue;
        }
        // maximise number of 6
        
        for(int i=0;i<=6;++i){
            if((N-i*4)%6==0){
                printf("%lld ",(N-i*4)/6+i);
                break;
            }
        }
        // maximise number of 4

        for(int i=0;i<=4;++i){
            if((N-i*6)%4==0){
                printf("%lld ",(N-i*6)/4+i);
                break;
            }
        }
        printf("\n");
    }
}