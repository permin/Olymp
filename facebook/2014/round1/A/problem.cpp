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

void solveTest() {
    string s;
    ll n;
    cin >> s >> n;
    int alpha = s.size();
    --n;
    ll am = alpha;
    int len = 1;
    while (n > am - 1) {
        n -= am;
        ++len;
        if (numeric_limits<ll>::max() / alpha < am)
            break;
        am *= alpha;
    }
    vector<int> res(len);
    for (int i = 0; i < len; ++i) {
        res[len - 1 - i] = n % alpha;
        n /= alpha;
    }
    assert(n == 0);
    for (int i = 0; i < len; ++i) {
        cout << s[res[i]];
    }
}

int main() {
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        cout << "Case #"<<test+1<<": ";
        solveTest();
        cout << endl;
    }
    return 0;
}
