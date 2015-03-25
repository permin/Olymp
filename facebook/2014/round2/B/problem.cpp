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

struct PairPair {
    pii first;
    pii second;
    int maxSum;
    int maxCard;
};

void f(pii& a) {
    if (a.first < a.second)
        swap(a.first, a.second);
}

PairPair make(pii a, pii b) {
    f(a);
    f(b);
    PairPair x;
    x.first = a;
    x.second = b;
    x.maxSum = max(a.first+a.second, b.first +b.second);
    x.maxCard = max(max(a.first, a.second), max(b.first, b.second));
    return x;
}

bool operator<(const PairPair& x, const PairPair& y) {
    if (pii(x.maxSum, x.maxCard) != pii(y.maxSum, y.maxCard))
        return pii(x.maxSum, x.maxCard) < pii(y.maxSum, y.maxCard);
    return make_pair(x.first,x.second) < make_pair(y.first, y.second);
}

void solveTest() {
    int n, h;
    cin >> n >> h;
    set<PairPair> q;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            for (int a = 1; a <= n; ++a)
                for (int b = a + 1; b <= n; ++b) {
                    if (a == i || a == j || b == j || b == i)
                        continue;
                    q.insert(make(pii(i,j),pii(a,b)));
                }
        }
    map<pii, char> cache;
    while(h --> 0) {
        int c1, c2;
        cin >> c1 >> c2;
        if (c1 > c2)
            swap(c1, c2);
        if (cache.count(pii(c1,c2))) {
            cout << cache[pii(c1,c2)];
            continue;
        }
        ll good = 0;
        for (int i = 1; i <= n; ++i) {
            if (i == c1 || i == c2)
                continue;
            for (int j = i + 1; j <= n; ++j) {
                if (j == c1 || j == c2)
                    continue;
                if (i + j > c1 + c2 || (i + j == c1 + c2 && max(i,j) > max(c1, c2)))
                    continue;
                set<PairPair> q2(q);
                for (int k = 1; k <= n; ++k) {
                    q2.erase(make(pii(c1,c2), pii(i, k)));
                    q2.erase(make(pii(c1,c2), pii(j, k)));
                    q2.erase(make(pii(c1,k), pii(i, j)));
                    q2.erase(make(pii(c2,k), pii(i, j)));
                }
                q2.erase(make(pii(c1,i), pii(c2, j)));
                q2.erase(make(pii(c2,i), pii(c1, j)));
                good += std::distance(q2.begin(), q2.lower_bound(make(pii(c1,c2),pii(c1,c2))));
            }
        }
        good /= 6;
        ll total = 1LL * (n - 2) * (n- 3) * (n - 4) * (n - 5) * (n - 6) * (n - 7);
        total /= 8;
        debug(1.0 * good / total);
        if (4 * good > total)
            cache[pii(c1,c2)] = 'B';
        else
            cache[pii(c1,c2)] = 'F';
        cout << cache[pii(c1,c2)];
    }
    cout << "\n";
}

int main() {
    int tests;
    cin >> tests;
    for (int i = 0; i < tests; ++i) {
        cout << "Case #"<<i+1<<": ";
        solveTest();
    }
    return 0;
}
