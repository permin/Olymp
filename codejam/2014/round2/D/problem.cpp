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
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

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

int maxNodes;
int num;

int f(const vector<string>& s) {
    set<string> r;
    for (int i = 0; i < s.size(); ++i) {
        for (int l = 0; l <= s[i].size(); ++l) {
            r.insert(s[i].substr(0, l));
        }
    }
    return r.size();
}

void rec(vector<string>& s, vector<vector<string>>& distr) {
    if (s.empty()) {
        for (int i = 0; i < distr.size(); ++i) {
            if (distr[i].empty())
                return;
        }
        int curSum = 0;
        for (int i = 0; i < distr.size(); ++i) {
            curSum += f(distr[i]);
        }
        if (curSum > maxNodes) {
            maxNodes = curSum;
            num = 1;
        } else if (curSum == maxNodes) {
            ++num;
        }
        return;
    }
    string x = s.back();
    s.pop_back();
    for (int i = 0; i < distr.size(); ++i) {
        distr[i].push_back(x);
        rec(s, distr);
        distr[i].pop_back();
    }
    s.push_back(x);
}

string solveSmall(vector<string> s, int servers) {
    stringstream o;
    maxNodes = 0;
    num = 0;
    vector<vector<string>> c(servers);
    rec(s, c);
    o << maxNodes << " " << num;
    return o.str();
}

void solveTest() {
    int n, m;
    cin >> m >> n;
    vector<string> s(m);
    for (int i = 0; i < m; ++i) {
        cin >> s[i];
    }
    cout << solveSmall(s, n) << "\n";
}

int main() {
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #" << t + 1 << ": ";
        solveTest();
    }
    return 0;
}
