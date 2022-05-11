#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class Trie {
public:
    Trie() {
        this->root = new node();
    }

    void add(ll x) {
        vector<int> vc = parse(x);
        root = insert(root, vc, 0);
    }
    
    ll query(ll x) {
        ll ret = 0, i, j = 0;
        vector<int> vc = parse(x);
        node *curr = root;
        for (i = 0 ; i < 19; ++i) {
            int mx = -1, id = -1;
            for (j = 0 ; j < 10; ++j) {
                if (curr->child[j] != NULL) {
                    if (mx < (j + vc[i]) % 10) {
                        mx = (j + vc[i]) % 10;
                        id = j;
                    }
                }
            }   

            curr = curr->child[id];
            ret = ret * 10 + mx;
        }
        return ret;
    }
    
private:
    struct node {
        int cnt;
        node *child[10];
        node() {
            for (int i = 0 ; i < 10; ++i) {
                this->child[i] = NULL;
            }    
            this->cnt = 0;
        }
    };
    
    node *root;
    
    int size(node *rt) {
        return rt == NULL ? 0 : rt->cnt;
    }
    
    node *insert(node *rt, vector<int> &a, int pos) {
        int sz = a.size();
        if (pos > sz) return rt;
        if (pos == sz) {
            rt->cnt++;
            return rt;
        }
        
        if (rt->child[a[pos]] == NULL) {
            rt->child[a[pos]] = new node();
        }
        
        rt->child[a[pos]] = insert(rt->child[a[pos]], a, pos + 1);
        rt->cnt = 0;
        for (int i = 0 ; i < 10; ++i) rt->cnt += size(rt->child[i]);
        return rt;
    }
    
    vector<int> parse(ll x) {
        vector<int> ret = vector<int>(19, 0);
        int idx = 18;
        while (x > 0) {
            ret[idx--] = x % 10;
            x /= 10;
        }
        return ret;
    }
};

Trie t = Trie();

int main() {
    int N;
    scanf("%d", &N);
    int i;
    ll ans = 0;
    for (i = 1; i <= N; ++i) {
        ll v;
        scanf("%lld", &v);
        if (i == 1) {
            t.add(v);
        } else {
            ans = max(ans, t.query(v));
            t.add(v);
        }
    }

    printf("%lld\n", ans);
    return 0;
}