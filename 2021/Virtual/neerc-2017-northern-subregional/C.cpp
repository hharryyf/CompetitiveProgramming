#include <bits/stdc++.h>
#define MAX_SIZE 1000111
typedef long long ll;
using namespace std;
#define FILEIO

int cnt[27][27];
char s[MAX_SIZE];
char bad[9] = {'a', 'e', 'i', 'o', 'u', 'w', 'y'};
char idx[20] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 
                'p', 'q', 'r', 's', 't', 'v', 'x', 'z'};
map<char, int> mp;
int ok[20];
void openfile(string filename="consonant") {
    string input = filename;
    input.append(".in");
    string output = filename;
    output.append(".out");
    freopen(input.c_str(), "r", stdin);
    freopen(output.c_str(), "w", stdout);
}

int main() {
    #ifdef FILEIO
    openfile();
    #endif
    set<char> invalid;
    for (int i = 0 ; i < 7; ++i) invalid.insert(bad[i]);
    scanf("%s", s);
    int i, len = strlen(s), j;
    for (i = 0 ; i < len; ++i) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 'a' - 'A';
    }

    for (i = 0 ; i < len - 1; ++i) {
        if (invalid.find(s[i]) != invalid.end() || invalid.find(s[i+1]) != invalid.end()) continue;
        cnt[s[i] - 'a'][s[i+1] - 'a']++;
    }

    for (i = 0 ; i < 19; ++i) {
        mp[idx[i]] = i;
    }

    int ans = 0, mask = 0;
    for (i = 0 ; i < (1 << 19); ++i) {
        int curr = 0;
        vector<int> low, high;
        for (j = 0; j < 19; ++j) {
            if ((1 << j) & i) {
                low.push_back(j);
            } else {
                high.push_back(j);
            }
        }

        for (auto v : low) {
            for (auto u : high) {
                curr += cnt[idx[v] - 'a'][idx[u] - 'a'];
                curr += cnt[idx[u] - 'a'][idx[v] - 'a'];
            }
        }

        if (ans < curr) {
            mask = i;
            ans = curr;
        }
    }


    for (i = 0 ; i < 19; ++i) {
        if (mask & (1 << i)) {
            ok[i] = 1;
        }
    }
    
    for (i = 0 ; i < len; ++i) {
        if (mp.find(s[i]) != mp.end() && ok[mp[s[i]]]) {
            printf("%c", s[i] + 'A' - 'a');
        } else {
            printf("%c", s[i]);
        }
    }
    return 0;
}