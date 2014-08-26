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

int gcd(int a, int b) {
    while (a) {
        b %=a;
        swap(a,b);
    }
    return b;
}

ll lcm(int a, int b) {
    return a / gcd(a,b) * b;
}

class LCMSet{
public:
    set<int> gen(vi a) {
        sort(all(a));
        set<int> res;
        res.insert(1);
        set<int> ans;
        for (int x: a) {
            //debug(res);
            if (res.count(x))
                continue;
            ans.insert(x);
            set<int> nr(res);
            for (int y: res) {
                ll z = lcm(y, x);
                if (z <= 1e9 + 5) {
                    for (int t: a) {
                        if (t % z == 0) {
                            nr.insert(z);
                        }
                    }
                }
            }
            res = nr;
        }
        //debug(res.size());
        return ans;
    }
    string equal(vector <int> A, vector <int> B) {
        //A.resize(25);
        //B.resize(25);
        if (gen(A) == gen(B))
            return "Equal";
        else
            return "Not equal";
    }
};

bool isPrime(int x) {
    for (int i = 2; i * i <= x; ++i)
        if (x % i == 0)
            return 0;
    return 1;
}

int main() {
    cerr << LCMSet().equal(
            	{161, 1453360, 18, 22781370, 8722, 3164153, 34622953, 10, 792323, 42821, 29950, 40, 179080, 64311, 50, 7574, 9273, 582, 37863540, 6, 598, 4195669, 394, 9, 7856, 7111240, 963, 484, 934036170, 8, 2720, 47, 25006, 41, 201274, 185, 781, 72, 5482741, 20, 5, 7284, 4840, 5734, 96, 748, 295, 39616150, 58967613}, {18, 37863540, 58967613, 3164153, 41, 9, 582, 394, 484, 8, 7111240, 5, 25006, 7856, 10, 5482741, 748, 201274, 781, 50, 9273, 31126524, 2720, 72, 5734, 185, 8722, 6, 963, 34622953, 42821, 598, 40, 7574, 7284, 29950, 64311, 20, 47, 22781370, 295, 1640, 161, 96, 4195669, 792323}) << "\n";

    return 0;
}
