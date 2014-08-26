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

#define debug(x) cerr << #x << ": "  << (x) << "\n";
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

char buf[1<<20];

class C {
    public:
        int x = 2;
};

int main() {
    vector<int> a;
    a.push_back(C());
    int t;
    cin >> t;
    while(t-->0) {
        scanf("%s", buf);
        string s(buf);
        bool ok = 1;
        int n = s.size();
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            int k = 0;
            for (int i = 0; i < n; ++i) {
                if (s[i] != ch)
                    continue;
                ++k;
                if (k == 3) {
                    if (i + 1 >= n || s[i + 1] != ch)
                        ok = 0;
                    ++i;
                    k = 0;
                }
            }
        }
        cout << (ok ? "OK": "FAKE") << "\n";
    }
    return 0;
}

