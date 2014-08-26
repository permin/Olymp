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

class HugeGraph{
public:
    ll gcd(ll x, ll y) {
        while(x) {
            y %= x;
            swap(x,y);
        }
        return y;
    }
    ll gcd(vector<ll> d) {
        ll g = d[0];
        for (int i = 0; i < d.size(); ++i)
            g = gcd(g, d[i]);
        return g;
    }
    long long countComponents(long long n, vector<long long> d) {
        sort(all(d));
        ll d1 = d[0];
        int i = 1;
        while (i < d.size() && d1 + d[i] - 1 < n) {
            d1 = gcd(d1, d[i]);
            ++i;
        }
        if (i == d.size())
            return d1;
        debug(d1);
        ll six = (n-1) % d1;
        debug(six);
        vector<ll> six_k;
        for (int j = i; j < d.size(); ++j)
            six_k.push_back(n % d[j]);
        sort(all(six_k));
        debug(six_k);
        vector<ll> deltas;
        for (int x = 0; x < six_k.size(); ++x)
            for (int y = x + 1; y < six_k.size(); ++y)
                deltas.push_back(six_k[y] - six_k[x]);
        ll g = gcd(deltas);
        ll k = six_k.back() - six;
        g = gcd(g, abs(six_k.back() - six));
        if (k >= 0) {
            ll upper = six_k.back();
            ll lower = -k;
            debug(lower);
            debug(upper);
            ll rem = upper - lower + 1;
            rem = min(rem, d1);
            return g + d1 - rem;
        } else  {
            ll upper = six;
            ll a = six + k;
            ll b = -k;
            ll lower = 0;
            ll rem = 0;
            debug(upper);
            debug(a);
            debug(b);
            debug(lower);
            if (a < b)
                rem = upper - lower + 1;
            else
                rem = (upper - a + 1) + (b - lower + 1);
            rem = min(rem, d1);
            return g + d1 - rem;
        }

    }
};

int main() {
    HugeGraph A;
    //debug(A.countComponents(5, {2}));
    //debug(A.countComponents(6, {2,3}));
    //debug(A.countComponents(10, {6, 8, 9}));
    //debug(A.countComponents(100, {10, 20, 30, 40, 50, 60, 70, 80, 90}));
    debug(A.countComponents(33, {30, 29, 26, 15}));
}
