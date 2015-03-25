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

bool isPrime(int x) {
    if (x < 2)
        return 0;
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return false;
    return true;
}

const int BOUND = 50;

vector<int> smallPrimes;
vector<int> bigPrimes;

vector<set<int>> numbers;
vector<vector<int>> subs;

int solve(int pos, const vi& a, int mask, int big, viii& dp) {
    int &res = dp[pos][mask][big];
    if (res >= 0)
        return res;
    if (pos == a.size())
        return res = 0;
    res = 1e9;
    if (res > bigPrimes[big] + solve(pos + 1, a, mask, big + 1, dp)) {
        res = bigPrimes[big] + solve(pos + 1, a, mask, big + 1, dp);
    }
    //res = min(res, bigPrimes[big] + solve(pos + 1, a, mask, big + 1, dp));
    /*if (a[pos] <= 0 && pos == 0) {
        res = min(res, 0 + solve(pos + 1, a, mask, big, dp));
    }*/
    if (a[pos] <= 1) {
        res = min(res, 1 + solve(pos + 1, a, mask, big, dp));
    }
    for (int sub: subs[mask]) {
        assert((sub & mask) == sub);
        if (res > *numbers[sub].lower_bound(a[pos]) + solve(pos + 1, a, mask ^ sub, big, dp)) {
            res = *numbers[sub].lower_bound(a[pos]) + solve(pos + 1, a, mask ^ sub, big, dp);
        }
    }
    return res;
}

void solveTest() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = ((a[i] + k - 1) / k);
    }
    debug(b);
    sort(all(b));
    viii dp(n + 1, vii(1 << smallPrimes.size(), vi(n + 1, -1)));
    int res = solve(0, b, (1 << smallPrimes.size()) - 1, 0, dp);
    {
        int cur = 0;
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            if (b[i] <= (i != 0)) {
                cur += -b[i] + (i != 0);
            } else {
                ok = 0;
            }
        }
        if (ok)
            res = min(res, cur);
    }

    debug(res);
    cout << res * k - accumulate(all(a), 0);
}

void gen(int cur, int pos, const vi& p, set<int>& res) {
    if (cur > 1 && cur <= BOUND * BOUND) {
        res.insert(cur);
    }
    if (pos == p.size())
        return;
    for (int i = 0; cur <= BOUND * BOUND;++i) {
        gen(cur, pos + 1, p, res);
        cur *= p[pos];
    }
}

int main() {
    for (int i = 2; i <= BOUND; ++i) {
        if (isPrime(i))
            smallPrimes.push_back(i);
    }
    {
        int b = BOUND;
        ++b;
        while (bigPrimes.size() < 20) {
            if (isPrime(b))
                bigPrimes.push_back(b);
            ++b;
        }
    }
    debug(smallPrimes);
    debug(bigPrimes);

    numbers.resize(1 << smallPrimes.size());
    subs.resize(1 << smallPrimes.size());
    for (int mask = 0; mask < (1 << smallPrimes.size()); ++mask) {
        vector<int> p;
        for (int i = 0; i < smallPrimes.size(); ++i) {
            if (mask & (1 << i))
                p.push_back(smallPrimes[i]);
        }
        //debug(p);
        gen(1, 0, p, numbers[mask]);
        //debug(numbers[mask]);
    }
    int sumLen = 0;
    for (int mask = 0; mask < (1 << smallPrimes.size()); ++mask) {
        for (int sub = mask; sub; sub = (sub - 1) & mask) {
            int c = 1;
            for (int i = 0; i < smallPrimes.size(); ++i) {
                if (c > bigPrimes.back())
                    break;
                if ((sub & (1 << i)) != 0)
                    c *= smallPrimes[i];
            }
            if (c < bigPrimes.back()) {
                subs[mask].push_back(sub);
            }
        }
        sumLen += subs[mask].size();
    }
    debug(sumLen);


    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        cout << "Case #"<<test+1<<": ";
        solveTest();
        cout << endl;
    }
    return 0;
}
