/*
   part of the code (graph constructing part) was done by Ali
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int , int> pii;
typedef long double ld;

const int N = 1e6+10 , mod = 1e9+7;

vector <int> g[N] , ids[N];
int num = 1 , nxt[N][2];

inline bool cmp(pair <string , int> &a , pair <string , int> &b){
   return a.first.length() < b.first.length();
}


int cmpid[N], low[N], visited[N], instack[N];
stack<int> st;
int cnt, cid = 1;

void tarjan(int v) {
    st.push(v);
    instack[v] = 1;
    visited[v] = low[v] = ++cnt;
    for (auto nv : g[v]) {
        if (!visited[nv]) {
            tarjan(nv);
            low[v] = min(low[v], low[nv]);
        } else if (instack[nv]) {
            low[v] = min(low[v], visited[nv]);
        }
    }

    if (low[v] == visited[v]) {
        while (st.top() != v) {
            instack[st.top()] = 0;
            cmpid[st.top()] = cid;
            st.pop();
        }

        cmpid[st.top()] = cid++;
        instack[st.top()] = 0;
        st.pop();
    }
}


void solve(){
   int n;
   cin >> n;
   string s[2 * n];
   vector < pair <string , int> > vec;
   for(int i = 0 ; i < n ; i++){
      cin >> s[i];
      int m = s[i].length();
      int id = -1;
      for(int j = 0 ; j < m ; j++){
         if(s[i][j] == '?'){
            id = j;
         }
      }
      if(id == -1){
         s[i + n] = s[i];
      }
      else{
         s[i][id] = '0';
         s[i + n] = s[i];
         s[i + n][id] = '1';
      }
      vec.push_back({s[i] , i});
      vec.push_back({s[i + n] , i + n});
   }
   sort(vec.begin() , vec.end() , cmp);
   for(int i = 0 ; i < 2 * n ; i++){
      string st = vec[i].first;
      int id = vec[i].second;
      int cur = 0;
      int m = st.length();
      vector <int> ins;
      int len = 0;
      for(int j = 0 ; j < m ; j++){
         if(!nxt[cur][st[j] - '0']){
            nxt[cur][st[j] - '0'] = num++;
         }
         len++;
         cur = nxt[cur][st[j] - '0'];
         for(int v : ids[cur]){
            ins.push_back(v);
         }
         if(ins.size() > len * 2){
            cout << "NO";
            return;
         }
      }
      for(int myid : ins){
         int othid = id + n;
         if(id >= n){
            othid = id - n;
         }
         int othid2 = myid + n;
         if(myid >= n){
            othid2 = myid - n;
         }
         g[myid].push_back(othid);
         g[id].push_back(othid2);
         // cout << id << " " << myid << " " << s[id] << " " << s[myid] << endl;
      }
      ids[cur].push_back(id);
   }

    int i;
    for (i = 0 ; i < 2 * n; ++i) {
        if (!visited[i]) {
            tarjan(i);
        }
    }

    for (i = 0 ; i < n; ++i) {
        if (cmpid[i] == cmpid[i + n]) {
            printf("NO\n");
            return;
        }
    }

    printf("YES\n");

    for (i = 0 ; i < n; ++i) {
        if (cmpid[i] < cmpid[i + n]) {
            printf("%s\n", s[i].c_str());
        } else {
            printf("%s\n", s[i+n].c_str());
        }
    }
}

int32_t main(){
   freopen("binary.in" , "r" , stdin);
   freopen("binary.out" , "w" , stdout);
   ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
   int t = 1;
   // cin >> t;
   int cur = 1;
   while(t--){
      // cout << "Case #" << cur++ << ": ";
      solve();
   }
   return 0;
}