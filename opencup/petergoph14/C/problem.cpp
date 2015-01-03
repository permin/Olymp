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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

/*int MAXN = 1000*10;
int K = 10;
int chainsNum = 345;*/
int MAXN = 121;
int K = 10;
int chainsNum = 10;

/*const int MAXN = 3;
const int K = 2;
const int chainsNum = 2;*/

/*const int MAXN = 100;
const int K = 5;
const int chainsNum = 10;*/

class InterConsole {
public:

    bool le(int i, int j) {
        if (c_.count(pii(i,j)))
            return c_[pii(i,j)];
        cout << "? " << i+1 << " " << j+1 << std::endl;
        string s;
        cin >> s;
        bool r = s[0] == '<';
        c_[pii(i,j)] = r;
        c_[pii(j,i)] = !r;
        return r;
    }
    bool guess(vi ans) {
        cout << "! ";
        for (int i = 0 ;i < ans.size(); ++i) {
            cout << ans[i] + 1 << " ";
        }
        cout << std::endl;
        exit(0);
        return 1;
    }
    map<pair<int, int>, bool> c_;

};

class InterDummy {
public:
    InterDummy() {
        req = 0;
        for (int i = 0; i < MAXN; ++i)
            p.push_back(i);
        random_shuffle(all(p));
        //debug(p);
    }
    bool le(int i, int j) {
        if (c_.count(pii(i,j)))
            return c_[pii(i,j)];
        ++req;
        c_[pii(i,j)] = p[i] < p[j];
        c_[pii(j,i)] = p[j] < p[i];
        return p[i] < p[j];
    }
    bool guess(vi ans) {
        for (int i = 0 ;i <K; ++i) {
            if (p[ans[i]] != i)
                return 0;
        }
        return 1;
    }
    int req;
private:
    map<pair<int, int>, bool> c_;
    vi p;
};

typedef InterDummy Inter;
//typedef InterConsole Inter;

Inter oracle;

class C {
    public:
    explicit C(int x=0) :x(x){}
    bool operator<(const C&c) const {
        return oracle.le(x, c.x);
    }
    bool operator>(const C&c) const {
        return oracle.le(c.x, x);
    }
    int x;
};

typedef vector<pair<C, bool>> Chain; //index alive

int minIndex(const Chain& chain) {
    int r = -1;
    for (int i = 0; i < chain.size(); ++i) {
        if (!chain[i].second)
            continue;
        if (r == -1) {
            r = i;
        } else {
            if (chain[i].first < chain[r].first)
                r = i;
        }
    }
    assert(r != -1);
    return r;
}

template<class T>
void siftDown(vector<T>& heap, int pos) {
    int left = pos * 2 + 1;
    int right = left + 1;
    if (left >= heap.size())
        return;
    int childToSwap = left;
    if (right < heap.size() && heap[right] < heap[left]) {
        childToSwap = right;
    }
    if (heap[childToSwap] < heap[pos]) {
        swap(heap[childToSwap], heap[pos]);
        pos = childToSwap;
        siftDown(heap, pos);
    }
}

ostream& operator << (ostream& o, const C& c) {
return o << "C(" <<c.x<<")";}

struct G{
    bool operator()(const pair<C, int>& x, const pair<C, int>& y) const {
        return x > y;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    //cin >> MAXN >> K;
    //chainsNum = 345;
    if (MAXN == 3) {
        cout << "! 1 2 3" << std::endl;
        return 0;
    }
    //assert(MAXN == 1000*10);
    int chainLen = (MAXN + chainsNum - 1) / chainsNum;
    vector<Chain> chains(chainsNum);
    for (int i = 0; i < chainsNum; ++i) {
        for (int j = i * chainLen; j < (i+1)*chainLen && j < MAXN; ++j) {
            chains[i].push_back(make_pair(C(j), true));
        }
    }

    vector<pair<C, int>> heap; // value chain_index
    for (int i = 0; i < chainsNum; ++i) {
        //debug(i);
        //debug(chains[i].size());
        int mi = minIndex(chains[i]);
        //debug(mi);
        chains[i][mi].second = false;
        heap.push_back(make_pair(chains[i][mi].first, i));
    }
    make_heap(all(heap), G());

    //debug(heap);
    vector<int> ans(K, -1);
    for (int i = 0; i < K; ++i) {
        //debug(i);
        ans[i] = heap[0].first.x;
        if (i == K - 1)
            continue;
        int chainIndex = heap[0].second;
        int mi = minIndex(chains[chainIndex]);
        chains[chainIndex][mi].second = 0;
        heap[0].first = chains[chainIndex][mi].first;
        siftDown(heap, 0);
        //debug(heap);
    }
    //debug(ans);
    //debug(oracle.req);
    //debug(oracle.guess(ans));
    std::cout << oracle.guess(ans) << "\n";
    return 0;


/*    while(true) {
        vector<C> c;
        int n = 10*1000;
        for (int i = 0; i < n; ++i) {
            c.push_back(C(i));
        }
        random_shuffle(all(c));
        num = 0;
        make_heap(all(c));

        //std::nth_element(c.begin(), c.begin() + 10, c.end());
        cout << num << "\n";
    }*/
    return 0;
}
