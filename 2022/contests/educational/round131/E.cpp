#pragma GCC optimize(3)
#pragma GCC optimize(2)
// #define D
#define BLOCK 450
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
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
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
using namespace std;
typedef long long ll;
 
const ll mod = 1e9 + 7;
const int inf32 = 19260817;
inline ll add(ll x,ll y){
    return ((x + y) % mod + mod) % mod;
}
 
inline ll mul(ll x,ll y){
    return x * y % mod;
}
 
inline ll qpow(ll x,ll n){
    ll ret= 1;
    while(n > 0){
        if(n & 1) ret = mul(ret, x);
        x = mul(x, x);
        n >>= 1;
    }
 
    return ret;
}
 
ll gcd(ll n,ll m){
    return n==0?m:gcd(m%n,n);
}

 

int N,M;
bool can_suf[5005][5005],can_pre[5005][5005];
int suf[5005][5005],pre[5005][5005];
char s[5005],t[5005];
int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(0); 
    cout.tie(0);
    int T;
    cin>>T;
    while(T--){
        cin>>N>>M;
        cin>>(s+1);
        cin>>(t+1);
        for(int i=0;i<=N+1;++i){
            for(int j=0;j<=M+1;++j){
                can_suf[i][j]=can_pre[i][j]=false;
                suf[i][j]=-inf32;
                pre[i][j]=inf32;
            }
        }
        // check if prefix can do
        for(int i=0;i<=N;++i)can_pre[i][0]=true;
        for(int i=0;i<=N + 1;++i)can_suf[i][M+1]=true;        
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                if(s[i]==t[j]){
                    can_pre[i][j]=can_pre[i-1][j-1];
                }
                else{
                    can_pre[i][j]=can_pre[i-1][j];
                }
            }
        }
        // check if suffix can do
        for(int i=N;i>=1;--i){
            for(int j=M;j>=1;--j){
                if(s[i]==t[j]){
                    can_suf[i][j]=can_suf[i+1][j+1] | can_suf[i+1][j];
                }
                else{
                    can_suf[i][j]=can_suf[i+1][j];
                }
            }
        }
        // pre[i][j] = s[1...i] match with t[1...j], what is the minimal index our 
        // cursor can end up with
        for(int i=0;i<=N;++i)pre[i][0]=i;
        for(int i=1;i<=N;++i){
            for(int j=1;j<=M;++j){
                if(can_pre[i][j]==false)continue;
                if(s[i]==t[j]){
                    pre[i][j]=min(
                        pre[i][j],
                        min(
                            i,
                            pre[i-1][j-1]
                        )
                    );
                }
                else{
                    pre[i][j]=i;
                }
                debug("pre[%d][%d]=%d\n",i,j,pre[i][j]);
            }
        }
        for(int i=0;i<=N + 1;++i)suf[i][M+1]=i;
        for(int i=N;i>=1;--i){
            for(int j=M;j>=1;--j){
                if(can_suf[i][j]==false)continue;
                if(s[i]==t[j]){
                    suf[i][j]=max(
                        suf[i][j],
                        max(
                            i,
                            suf[i+1][j+1]
                        )
                    );
                }
                else{
                    suf[i][j]=i;
                }
                debug("suf[%d][%d]=%d\n",i,j,suf[i][j]);
            }
        }
        // merge result
        // s[1..i] = t[1...j] and s[i+1..N] = t[j+1..M]
        int ans=N+1-suf[1][1];
        for(int i=0;i<=N;++i){
            for(int j=0;j<=M;++j){
                if(can_pre[i][j]==false||can_suf[i+1][j+1]==false)continue;
                int val=0;
                val+=N+1-suf[i+1][j+1];
                val++; // go to beginning
                val+=pre[i][j]+i-j;
                ans=min(ans,val);
            }       
        }
        if(ans<inf32){
            cout<<ans<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
}