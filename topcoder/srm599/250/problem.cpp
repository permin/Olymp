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

class BigFatInteger{
public:
    vector<pii> f(int A) {
        vector<pii> r;
        for (int i = 2; i * i <= A; ++i) {
            if (A % i)
                continue;
            r.push_back(pii(i, 0));
            while(A % i == 0) {
                A /= i;
                r.back().second += 1;
            }
        }
        if (A > 1)
            r.push_back(pii(A,1));
        return r;
    }
    int minOperations(int A, int B) {
        vector<pii> r = f(A);

        int res = 0;
        for (int i = 0; i < r.size(); ++i) {
            res = max(res, g(r[i].second * B));
        }
        return res + r.size();
    }
    int g(int x) {
        int y = 0;
        while ((1 << y) < x)
            ++y;
        return y;
    }

};

int main() {
    debug(BigFatInteger().minOperations(12, 100));
    return 0;
}
