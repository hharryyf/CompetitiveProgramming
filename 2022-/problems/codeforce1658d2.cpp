#include <bits/stdc++.h>
//#define D
#ifdef D
#define debug(...) fprintf(stderr, __VA_ARGS__)
#else
#define debug(...)
#endif
#define MAX_SIZE 1048597
#define LEFT (index<<1)
#define RIGHT ((index<<1)|1)
#define MID ((l+r)>>1)
typedef long long ll;
using namespace std;

class Trie {
public:
	Trie() {
		this->root = new node();
    }
	
	void add(int x) {
		vector<int> vc = parse(x);
		root = insert(root, vc, 0);
	}
	
	void del(int x) {
		vector<int> vc = parse(x);
		root = remove(root, vc, 0);
	}
	
	int query_max(int x) {
		int ret = 0, i;
		vector<int> vc = parse(x);
		node *curr = root;
		for (i = 0 ; i < 31; ++i) {
			if (vc[i] == 0) {
				if (curr->child[1] != NULL) {
					ret = (ret << 1) + 1;
					curr = curr->child[1];
				} else {
					ret = ret << 1;
					curr = curr->child[0];
				}
			} else {
				if (curr->child[0] != NULL) {
					ret = (ret << 1) + 1;
					curr = curr->child[0];
				} else {
					ret = ret << 1;
					curr = curr->child[1];
				}
			}
		}
		return ret;
	}
	
    void removeall() {
        this->clear(root);
        this->root = new node();
    }

    int query_min(int x) {
		int ret = 0, i;
		vector<int> vc = parse(x);
		node *curr = root;
		for (i = 0 ; i < 31; ++i) {
			if (vc[i] != 0) {
				if (curr->child[1] != NULL) {
					ret = (ret << 1);
					curr = curr->child[1];
				} else {
					ret = (ret << 1) + 1;
					curr = curr->child[0];
				}
			} else {
				if (curr->child[0] != NULL) {
					ret = (ret << 1);
					curr = curr->child[0];
				} else {
					ret = (ret << 1) + 1;
					curr = curr->child[1];
				}
			}
		}
		return ret;
	}

private:
	struct node {
		int cnt;
		node *child[2];
		node() {
			this->child[0] = this->child[1] = NULL;
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
		rt->cnt = size(rt->child[0]) + size(rt->child[1]);
		return rt;
	}
	
    void clear(node *rt) {
        if (rt == NULL) return;
        for (int i = 0 ; i < 2; ++i) {
            clear(rt->child[i]);
        }
        delete rt;
    }

	node *remove(node *rt, vector<int> &a, int pos) {
		int sz = a.size();
		if (rt == NULL || pos > sz) return rt;
		if (pos == sz) {
			rt->cnt--;
			return rt;
		}
		
		rt->child[a[pos]] = remove(rt->child[a[pos]], a, pos + 1);
		if (!size(rt->child[a[pos]])) {
			delete rt->child[a[pos]];
			rt->child[a[pos]] = NULL;
		}
		
		rt->cnt = size(rt->child[0]) + size(rt->child[1]);
		return rt;
	}
	
	vector<int> parse(int x) {
		vector<int> ret = vector<int>(31, 0);
		int idx = 30;
		while (x > 0) {
			ret[idx--] = x & 1;
			x >>= 1;
		}
		return ret;
	}
};

Trie t = Trie();

int main() {
    int T;
    scanf("%d", &T);
    while (T-- > 0) {
        t.removeall();
        debug("here\n");
        int l, r;
        scanf("%d%d", &l, &r);
        vector<int> ret(r - l + 1);
        for (int i = 0 ; i < r - l + 1; ++i) {
            scanf("%d", &ret[i]);
            t.add(ret[i]);
            debug("insert %d\n", ret[i]);
        }

        debug("finish reading\n");
        int ans = -1;
        for (int i = 0; i < r - l + 1; ++i) {
            int v = l ^ ret[i];
            int minn = t.query_min(v), maxx = t.query_max(v);
            debug("x=%d, min=%d, max=%d\n", v, minn, maxx);
            if (t.query_min(v) == l && t.query_max(v) == r) {
                ans = v;
                break;
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}