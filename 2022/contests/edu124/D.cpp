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
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int main(){
    int N=read();
    vector<pii>vec(N+5);
    map<int,map<int,int>>pt;
    map<int,map<int,int>>vis;
    vector<pii>ans(N+5);
    for(int i=1;i<=N;++i){
        int x=read();
        int y=read();
        vec[i]={x,y};
        pt[x][y]=i;
        ans[i]={-1,-1};
    }
    queue<array<int,4>>q;
    for(int i=1;i<=N;++i){
        int x=vec[i].x;
        int y=vec[i].y;
        for(int j=0;j<4;++j){
            int nx=x+dir[j][0];
            int ny=y+dir[j][1];
            if(!pt[nx][ny])q.push({nx,ny,nx,ny});
        }
    }
    while(!q.empty()){
        auto cur=q.front();
        q.pop();
        int x=cur[0],y=cur[1],sx=cur[2],sy=cur[3];
        if(vis.find(x)!=vis.end()&&vis[x].find(y)!=vis[x].end())continue;
        vis[x][y]=1;
        for(int j=0;j<4;++j){
            int nx=x+dir[j][0];
            int ny=y+dir[j][1];
            if(vis.find(nx)!=vis.end()&&vis[nx].find(ny)!=vis[nx].end())continue;
            if(pt.find(nx)==pt.end()||pt[nx].find(ny)==pt[nx].end())continue;
            if(pt[nx][ny]&&ans[pt[nx][ny]]==make_pair(-1,-1)){
                ans[pt[nx][ny]]={sx,sy};
            }
            q.push({nx,ny,sx,sy});
        }
    }
    for(int i=1;i<=N;++i){
        printf("%d %d\n",ans[i].x,ans[i].y);
    }

    return 0;
}   
