#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <stack>
#include <deque>
#include <queue>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {o << "[";O__(o, v);o << "]";return o;}

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<vi> vii;
typedef vector<vii> viii;

const double PI = 3.1415926535897932384626433832795;
const double EPS = 1e-9;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

template<class T>
class FirstComponentSumMantainer {
    typedef pair<int, T> Pair;
    typedef multiset<Pair> C;
public:
    FirstComponentSumMantainer():
        sum_(0){}
    void insert(const Pair& x) {
        q.insert(x);
        sum_ += x.first;
    }
    void remove(const Pair& x) {
        auto it = q.find(x);
        remove(it);
    }
    bool empty() const {
        return q.empty();
    }
    void erase(typename C::iterator it) {
        sum_ -= it->first;
        q.erase(it);
    }
    typename C::iterator begin() {
        return q.begin();
    }
    typename C::iterator end() {
        return q.end();
    }
    const C& data() const {
        return q;
    }
    ll sum() const {
        return sum_;
    }
private:
    C  q;
    ll sum_;
};

class RectanglesAndHoles {
public:
    vi place(vi w, vi h) {
        //size_t n = h.size();
        vi res(w.size() * 3, 0);
        return makeOneWhole(h, w, res);
    }
    vi makeOneWhole(vi h, vi w, vi& res) {
        vi part1;
        vi part2;
        ll len = makePerfectPartition(h, w, part1, part2);
        debug(part1);
        debug(part2);
        assert(part1.size() + part2.size() +2 == h.size());
        int first, second;
        first = -1;
        second = -1;
        for (int i = 0; i < w.size(); ++i) {
            if (count(all(part1), i) + count(all(part2), i) == 0) {
                if (first == -1) {
                    first = i;
                } else {
                    second = i;
                }
            }
        }
        res[3 * first] = -w[first];
        res[3 * first + 1] = -h[first] / 2;

        res[3*second] = len;
        res[3*second + 1] = -h[second] / 2;

        debug(first);
        debug(second);

        /*{
            int x=0;
            for (int i = 0; i < part1.size(); ++i) {
                int id = part1[i];
                res[3 * id] = x;
                res[3 * id + 1] = 1;// + h[id];
                res[3*id+2] = 0;
                x += w[id];
            }
            assert(x==len);
        }*/
        {
            vector<int> h1, w1;
            for (int i= 0; i < part1.size(); ++i) {
                h1.push_back(h[part1[i]]);
                w1.push_back(w[part1[i]]);
            }
            makeSmartLine(h[first] + (-h[first]/2), h[second] + (-h[second]/2), h, w, part1, res);
        }
        makeSmartLine(h[first]/2, h[second]/2, h, w, part2, res);
        for (int id: part2) {
            res[3 * id + 1] = -res[3 * id + 1] - h[id];
        }
        return res;
        {
            int x=0;
            for (int i = 0; i < part2.size(); ++i) {
                int id = part2[i];
                res[3 * id] = x;
                res[3 * id + 1] = -1 - h[id];
                res[3*id+2] = 0;
                x += w[id];
            }
            assert(x==len);
        }
        //debug(res);

        return res;
    }
    void makeSmartLine(int y0, int y1, vector<int> h, vector<int> w, vector<int> id, vi& res) {
        vector<pii> data;
        for (int i = 0; i < id.size(); ++i) {
            data.push_back(MP(h[id[i]], id[i]));
        }
        sort(all(data));
        reverse(all(data));

        vi perm(id.size(), -1);
        int i = 0;
        int l = 0;
        int r = data.size() - 1;
        while (i < perm.size()) {
            perm[l++] = data[i++].second;
            if (i < perm.size()) {
                perm[r--] = data[i++].second;
            }
        }
        //debug(perm);
        int sum = 0;
        {
            for (int i: perm) {
                sum += h[i];
            }
        }
        int dy = y0 - y1;
        int curY = y0;
        int curX = 0;
        for (int i: perm) {
            res[3 * i] = curX;
            res[3 * i + 1] = curY;
            curX += w[i];
            if ((sum - h[i]) >= (dy + h[i])) {
                dy += h[i];
                curY += h[i];
            } else if ((sum - h[i]) >= dy) {

            } else {
                dy -= h[i];
                curY -= h[i];
                res[3 * i + 1] = curY;
            }
            sum -= h[i];
            //debug(res[3 * i + 1]);
            std::cerr << res[3 * i + 1] << " " << h[i] << "\n";
        }
        debug(y0);
        debug(y1);
        assert(sum == 0);
    }
    ll makePerfectPartition(vi h, vi w, vi& part1, vi& part2) {
        while(1) {
            vector<pair<int, pii>> xyi;
            for (int i = 0; i < h.size(); ++i) {
                xyi.push_back(MP(h[i], MP(w[i], i)));
            }
            random_shuffle(all(xyi));
            vector<int> seq;
            for (int i = 0; i + 2 < xyi.size(); ++i) {
                seq.push_back(xyi[i].second.first);
            }
            int sum = accumulate(all(seq), 0);
            if (sum&1)
                continue;
            sum /= 2;
            vector<int> dp(sum + 1);
            vector<int> prev(sum + 1, -1);
            vector<int> pos(1);
            dp[0]=1;
            for (int i = 0; i < seq.size(); ++i) {
                int sz = pos.size();
                for (int j = 0; j < sz; ++j) {
                    int p = pos[j];
                    if (p + seq[i] > sum)
                        continue;
                    int np = p + seq[i];
                    if (dp[np] == 0) {
                        dp[np] = 1;
                        prev[np] = i;
                        pos.push_back(np);
                    }
                }
            }
            if (dp[sum] == 0)
                continue;
            while(sum>0) {
                part1.push_back(xyi[prev[sum]].second.second);
                sum -= seq[prev[sum]];
            }
            sort(all(part1));
            for (int i = 0; i < xyi.size() - 2; ++i) {
                int id = xyi[i].second.second;
                if (!binary_search(all(part1), id))
                    part2.push_back(id);
            }
            return dp.size() - 1;
        }
    }
};

int main() {
    srand(2);
    int n;
    cin >> n;
    vector<int> A(n),B(n);
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    for (int i = 0; i < n; ++i)
        cin >> B[i];
    vi r = RectanglesAndHoles().place(A, B);
    for (int i = 0; i < n+n+n; ++i) {
        cout << r[i] << "\n";
    }

    return 0;
}
