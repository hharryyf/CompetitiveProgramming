#include <bits/stdc++.h>
#define MAX_SIZE 35011
typedef int ll;
using namespace std;

struct cars {
    ll v, t;
    int wt;
    bool operator < (cars other) {
        if (t != other.t) return t < other.t;
        return v < other.v;
    }
};

struct fraction {
    ll num, den;
    fraction(ll num = 1, ll den = 1) {
        this->num = num, this->den = den;
        this->reduce();
    }

    bool operator ==(fraction other) const {
        return other.den * num == other.num * den;
    }

    fraction operator +(fraction other) const {
        fraction ret;
        ret.num = other.den * num + other.num * den;
        ret.den = other.den * den;
        ret.reduce();
        return ret;   
    }

    fraction operator -(fraction other) const {
        other.num *= -1;
        fraction ret = fraction(num, den);
        ret = ret + other;
        ret.reduce();
        return ret;
    }

    void reduce() {
        //ll g = __gcd(abs(num), abs(den));
        // num /= g, den /= g;
        if (num < 0 && den < 0) {
            num *= -1, den *= -1;
        } else if (den < 0 && num > 0) {
            den *= -1, num *= -1;
        }

        if (num == 0) den = 1;
    }

    fraction operator *(fraction other) const {
        fraction ret;
        ret.num = other.num * num;
        ret.den = other.den * den;
        ret.reduce();
        return ret;
    }

    fraction operator /(fraction other) const {
        fraction ret = fraction(other.den * num, other.num * den);
        ret.reduce();
        return ret;
    }

    bool operator < (fraction other) const {
        return other.den * num < other.num * den;
    }

    bool operator > (fraction other) const {
        return other.den * num > other.num * den;
    }

    bool operator <= (fraction other) const {
        return other.den * num <= other.num * den;
    }

    bool operator >= (fraction other) const {
        return other.den * num >= other.num * den;
    }

    bool operator !=(fraction other) const {
        return other.den * num != other.num * den;
    }
};

// (start time, (end time, id))
map<int, map<fraction, int>> cnt;
vector<cars> tmp, car;
int N;

int main() {
    int i;
    while (scanf("%d", &N) != EOF) {
        tmp.clear(), car.clear(), cnt.clear();
        for (i = 0 ; i < N; ++i) {
            cars c;
            scanf("%d%d", &c.t, &c.v);
            c.wt = 1;
            tmp.push_back(c);
        }

        sort(tmp.begin(), tmp.end());
        vector<pair<int, vector<pair<fraction, int>>>> mp;

        for (i = 0 ; i < (int) tmp.size(); ++i) {
            if (i == 0 || tmp[i].v != tmp[i-1].v || tmp[i].t != tmp[i-1].t) {
                car.push_back(tmp[i]);
            } else {
                car[(int) car.size() - 1].wt++;
            }
        }

        for (i = 0 ; i < (int) car.size(); ++i) {
            // car[i].t + 100 / car[i].v
            fraction t = fraction(car[i].t * car[i].v + 100, car[i].v);
            cnt[car[i].t][t] = i;            
        }

        for (auto iter : cnt) {
            mp.emplace_back(iter.first, vector<pair<fraction, int>>());
            int sz = mp.size();
            for (auto it : iter.second) {
                mp[sz - 1].second.emplace_back(it.first, it.second);
            }
        }

        int sz = mp.size(), ans = 1;
        for (i = 0 ; i < sz; ++i) {
            fraction st = fraction(mp[i].first, 1);
            // for each car, we get the answer
            for (auto c : mp[i].second) {
                // map from t to count
                ans = max(ans, car[c.second].wt);
                map<fraction, int> tol;
                for (int j = i - 1; j >= 0; --j) {
                    if (mp[j].first + 100 < mp[i].first) break;
                    for (int k = mp[j].second.size() - 1; k >= 0; --k) {
                        if (c.first > mp[j].second[k].first) break;
                        // add the calculation thing
                        int id1 = c.second, id2 = mp[j].second[k].second;
                        fraction t = fraction(car[id1].v * car[id1].t - car[id2].v * car[id2].t, car[id1].v - car[id2].v);
                        tol[t] += car[mp[j].second[k].second].wt;
                    }
                }

                for (auto cc : mp[i].second) {
                    if (cc.second == c.second) continue;
                    tol[st] += car[cc.second].wt;
                }

                for (int j = i + 1; j < sz; ++j) {
                    if (mp[j].first - 100 > mp[i].first) break;
                    if (c.first.num > mp[j].first * c.first.den) break;
                    for (int k = mp[j].second.size() - 1; k >= 0; --k) {
                        if (st < mp[j].second[k].first) break;
                        // add the calculation thing
                        int id1 = c.second, id2 = mp[j].second[k].second;
                        fraction t = fraction(car[id1].v * car[id1].t - car[id2].v * car[id2].t, car[id1].v - car[id2].v);
                        tol[t] += car[mp[j].second[k].second].wt;
                    }
                }

                for (auto iter : tol) {
                    ans = max(ans, iter.second + car[c.second].wt);
                }
            }
        }

        printf("%d\n", ans);
    }
    return 0;
}