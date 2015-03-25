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
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;};

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

const size_t UNDEFINED_ID = -1;

struct Node {
    Node(): id(UNDEFINED_ID), inSubTree(0) {}
    std::map<char, std::unique_ptr<Node>> childs;
    size_t id;
    size_t inSubTree;
};

class Trie {
public:
    void add(const string& s, size_t id) {
        Node * cur = &root_;
        cur->inSubTree += 1;

        for (int i = 0; i < s.size(); ++i) {
            if (cur->childs.count(s[i]) == 0) {
                cur->childs[s[i]] = make_unique<Node>();
            }
            cur = cur->childs[s[i]].get();
            assert(cur != nullptr);
            cur->inSubTree += 1;
        }
        assert(cur->id == UNDEFINED_ID);
        cur->id = id;
    }
    size_t minStepsToDetermine(const std::string& s, size_t id) {
        Node * cur = &root_;
        size_t res = 0;
        do {
            cur = cur->childs[s[res]].get();
            assert(cur != nullptr);
            ++res;
        } while(cur->id != id && cur->inSubTree > 1);
        return res;
    }
private:
    Node root_;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int tests = 0;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #" << t + 1 << ": ";
        int n;
        cin >> n;
        Trie dict;
        size_t res = 0;
        if (n == 1) {
            string s;
            cin >> s;
            cout << "1\n";
            continue;
        }
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            dict.add(s, i);
            res += dict.minStepsToDetermine(s, i);
        }
        cout << res << "\n";
    }
    return 0;
}
