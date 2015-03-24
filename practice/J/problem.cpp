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

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <memory.h>

// van Emde Boas Tree by Arthur "Inviz" Khashaev
// special for habrahabr :)

// This is a data structure used to store integers in bound [0; U), where U = 2^k

// Asymptotic complexity:
// Insert, Lookup, FindNext, Remove, etc -- O(log(log(U)))
// Space -- O(U)

#define NONE(K) (1ULL << K)

template <unsigned K>
class VebTree {
private:
        unsigned long long T_min, T_max;
        VebTree<(K >> 1)> *T[1ULL << (K >> 1)], *aux;
public:
        VebTree(): T_min(NONE(K)), aux(NULL) {
                memset(T, 0, sizeof(T));
        }

        ~VebTree() {
                delete aux;
                for (unsigned long long i = 0; i < (1ULL << (K >> 1)); ++i) {
                        delete T[i];
                }
        }

        inline bool empty() const {
                return T_min == NONE(K);
        }

        inline unsigned long long get_min() const {
                return T_min;
        }

        inline unsigned long long get_max() const {
                return T_max;
        }

        inline unsigned long long high(unsigned long long key) const {
                return key >> (K >> 1);
        }

        inline unsigned long long low(unsigned long long key) const {
                return key & ((1ULL << (K >> 1)) - 1ULL);
        }

        inline unsigned long long merge(unsigned long long high, unsigned long long low) const {
                return (high << (K >> 1)) + low;
        }

        void insert(unsigned long long key) {
                if (empty()) {
                        T_min = T_max = key;
                } else {
                        if (key < T_min) {
                                unsigned long long temp_key = key;
                                key = T_min;
                                T_min = temp_key;
                        }
                        if (key > T_max) {
                                T_max = key;
                        }
                        if (K != 1) {
                                unsigned long long key_high = high(key);
                                unsigned long long key_low = low(key);
                                if (T[key_high] == NULL) {
                                        T[key_high] = new VebTree<(K >> 1)>();
                                }
                                if (T[key_high]->empty()) {
                                        if (aux == NULL) {
                                                aux = new VebTree<(K >> 1)>();
                                        }
                                        aux->insert(key_high);
                                }
                                T[key_high]->insert(key_low);
                        }
                }
        }

        unsigned long long find_next(unsigned long long key) {
                if (key <= T_min) {
                        return T_min;
                }
                if (empty() || key > T_max) {
                        return NONE(K);
                }
                if (K == 1) {
                        return T_max == key ? key : NONE(K);
                }
                unsigned long long key_high = high(key);
                unsigned long long key_low = low(key);
                if (T[key_high] != NULL && key_low <= T[key_high]->get_max()) {
                        return merge(key_high, T[key_high]->find_next(key_low));
                } else if (aux != NULL) {
                        unsigned long long next_high = aux->find_next(key_high + 1);
                        if (next_high != NONE(K >> 1)) {
                                return merge(next_high, T[next_high]->get_min());
                        }
                }
                return NONE(K);
        }

        bool lookup(unsigned long long key) {
                if (key == T_min || key == T_max) {
                        return true;
                } else {
                        unsigned long long key_high = high(key);
                        unsigned long long key_low = low(key);
                        return T[key_high] != NULL && T[key_high]->lookup(key_low);
                }
        }
};

class Timer {
    double secondsSpent_;
    clock_t startTime_;

    double currentTime() const {
        return  startTime_ == -1 ? 0.0 : 1.0 * (clock() - startTime_) / CLOCKS_PER_SEC;
    }

public:
    Timer():
        secondsSpent_(0.0),
        startTime_(-1) {}

    double totalTime() const {
        return secondsSpent_ + currentTime();
    }

    void print() const {
        std::cerr << totalTime() << " sec.\n";
    }

    void start() {
        assert(startTime_ == -1);
        startTime_ = clock();
    }

    void pause() {
        secondsSpent_ += currentTime();
        assert(startTime_ != -1);
        startTime_ = -1;
    }
};

std::vector<size_t> generateRandomArray(size_t maxValue, size_t length) {
    std::random_device s;
    std::vector<size_t> a;
    for (int i = 0; i < length; ++i)
        a.push_back(s() % (1 + maxValue));
    return a;
}


int main() {
    vector<size_t>  a = generateRandomArray(INF/2, 1000*1000*30);
    sort(all(a));
    a.erase(std::unique(all(a)), a.end());
    random_shuffle(all(a));
    debug(a.size());

    {
        Timer t;
        t.start();
        {
        set<size_t> rbtree;
        for (size_t x: a) {
            assert(rbtree.count(x) == 0);
            rbtree.insert(x);
        }
        }
        t.pause();
        t.print();
    }
    {
        Timer t;
        t.start();
        {
        VebTree<32> tree;
        for (size_t x: a) {
            assert(tree.find_next(x) != x);
            tree.insert(x);
        }
        }
        t.pause();
        t.print();
    }
    return 0;
}
