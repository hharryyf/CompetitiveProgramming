// not my code, Edward coded it in contest
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
const int MAXN=1e5+10;
int fa[MAXN*10];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void merge(int x,int y){x=find(x);y=find(y);if(x!=y){fa[x]=y;}}
int main(){
    int t=read();
    while(t--){
        int N=read();
        int tot=0;
        vector<array<int,3>>a(N+5); //(c,l,r)
        vector<int>tmp;
        for(int i=1;i<=N;++i){
            for(int j=0;j<3;++j){
                a[i][j]=read();
                if(j>0){
                    tmp.push_back(a[i][j]);
                    tmp.push_back(a[i][j]+1);
                }
            }
        }
        sort(tmp.begin(),tmp.end());
        map<int,int>mp;
        for(int i:tmp){
            if(!mp[i]){
                mp[i]=++tot;
            }
        }
        vector<vector<pii>>add(tot+10);
        vector<vector<pii>>del(tot+10);
        for(int i=1;i<=N;++i){
            int l=a[i][1],r=a[i][2],c=a[i][0];
            add[mp[l]].push_back({i,c});
            del[mp[r+1]].push_back({i,c});
            fa[i]=i;
        }
        set<int>alive[2];
        for(int i=1;i<=tot+5;++i){
            for(auto e:del[i]){
                int color=e.y,id=e.x;
                if(alive[color].find(id)!=alive[color].end()){
                    alive[color].erase(id);
                }
            }
            for(auto e:add[i]){
                int color=e.y,id=e.x;
                alive[color].insert(id);
            }
            if(!alive[0].empty()&&!alive[1].empty()){
                vector<int>vec;
                for(int j=0;j<2;++j)for(int x:alive[j])vec.push_back(x);
                for(int j=0;j+1<vec.size();++j)merge(vec[j],vec[j+1]);
                for(int j=0;j<2;++j){
                    int max_len=0;
                    for(int x:alive[j]){
                        max_len=max(max_len,a[x][2]);
                    }
                    set<int>nex;
                    for(int x:alive[j])if(a[x][2]==max_len)nex.insert(x);
                    alive[j]=nex;
                }
            }
        }   
        set<int>ans;
        for(int i=1;i<=N;++i)ans.insert(find(i));
        printf("%d\n",(int)ans.size());
    }
}   