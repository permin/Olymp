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

bool isP(string s) {
    for (int i = 0; i < s.size(); ++i)
        if (s[i] != s[s.size() - 1 - i])
            return 0;
    return 1;
}

string m(string s) {
    string res;
    for (int i = 0; i < s.size(); ++i) {
        vector<string> d(2);
        char ch = s[i];
        ch = toupper(ch);
        d.push_back("ABC");
        d.push_back("DEF");
        d.push_back("GHI");
        d.push_back("JKL");
        d.push_back("MNO");
        d.push_back("PQRS");
        d.push_back("TUV");
        d.push_back("WXYZ");
        for (int j = 0; j < d.size(); ++j)
            for (int k = 0; k < d[j].size(); ++k)
                if (d[j][k] == ch) {
                    res += ('0' + j);
                    //debug(j);
                    //debug(k);
                    //debug(res);
                }
    }
    return res;
}

int main() {
    int t;
    cin >> t;
    while(t-->0) {
        string s;
        cin >> s;
        s = m(s);
        debug(s);
        cout << (isP(s) ? "YES": "NO") << "\n";
    }
    return 0;
}

