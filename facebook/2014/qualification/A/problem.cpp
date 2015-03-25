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

int main() {
    size_t tests;
    cin >> tests;
    for (size_t test = 0; test < tests; ++test) {
        cout << "Case #" << test + 1 << ": ";
        size_t n;
        cin >> n;
        size_t minX, minY, maxX, maxY;
        minX = minY = n;
        maxX = maxY = 0;
        vector<string> image(n);
        for (size_t i = 0; i < n; ++i) {
            cin >> image[i];
        }
        debug(image);
        size_t num = 0;
        for (size_t x = 0; x < n; ++x)
            for (size_t y = 0; y < n; ++y) {
                if (image[x][y] == '.')
                    continue;
                ++num;
                minX = min(minX, x);
                minY = min(minY, y);

                maxX = max(maxX, x);
                maxY = max(maxY, y);
            }
       size_t dx = maxX - minX + 1;
       size_t dy = maxY - minY + 1;
       cout << ((num == 0 || (num == dx * dy && dx == dy)) ? "YES": "NO") << "\n";
    }


    return 0;
}
