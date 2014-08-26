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

int f(int deques, int coins, int needed) {
    int inEvery = coins / deques;
    if (inEvery * deques >= needed)  {
        return needed;
    }
    int rem = coins - inEvery * deques;
    assert(rem >= 0);
    assert(rem < deques);

    int zero = deques - rem;
    int one = rem;

    int res = inEvery * deques;
    needed -= inEvery * deques;

    res += zero + min(one, needed);
    return res;
}

void solveTest() {
    int deques, coins, needed;
    cin >> deques >> coins >> needed;
    int res = f(deques, coins, needed);
    for (int i = 1; i <= deques; ++i) {
        res = min(res, f(i, coins, needed) + deques - i);
    }
    cout << res;
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
