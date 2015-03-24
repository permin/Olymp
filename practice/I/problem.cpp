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
typedef vector<size_t> vi;
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

vi path(size_t v, const vi& mu, const vi& phi) {
    vi res;
    set<size_t> s;
    while(res.empty() || res.back() != v) {
        if (s.count(v))
            break;
        res.push_back(v);
        s.insert(v);
        if (res.size() % 2 == 0) {
            v = phi[v];
        } else {
            v = mu[v];
        }
    }
    return res;
}

bool outer(size_t v, const vi& mu, const vi& phi) {
    return v == mu[v] || phi[mu[v]] != mu[v];
}

bool inner(size_t v, const vi& mu, const vi& phi) {
    return phi[mu[v]] == mu[v] && phi[v] != v;
}

bool outOfForest(size_t v, const vi& mu, const vi& phi) {
    return mu[v] != v && phi[v] == v && phi[mu[v]] == mu[v];
}

size_t first(const vi& a, const vi& b) {
    unordered_set<size_t> aa(all(a));
    for (int i = 0; i < b.size(); ++i) {
        if (aa.count(b[i]))
            return b[i];
    }
    return -1;
}

vi findMatching(const vii& al) {
    int n = int(al.size());
    vi mu(n);
    vi rho(n);
    vi phi(n);
    vector<bool> scanned(n);

    for (size_t i = 0; i < n; ++i) {
        mu[i] = phi[i] = rho[i] = i;
    }

    bool changed;
    do {
        set<size_t> A;

        cerr << "Outer: ";
        for (size_t i = 0; i < n; ++i) {
            if (outer(i, mu, phi))
                cerr << i << " ";
        }
        cerr << "\n";

        cerr << "Inner: ";
        for (size_t i = 0; i < n; ++i) {
            if (inner(i, mu, phi))
                cerr << i << " ";
        }
        cerr << "\n";
        debug(rho);

        cerr << "Matching:\n";
        for (size_t i = 0; i < n; ++i) {
            if (mu[i] == i)
                continue;
            if (A.count(i))
                continue;
            cerr << "\t" << i << " <-> " << mu[i] << "\n";
            A.insert(mu[i]);
        }

        cerr << "Forest:\n";
        for (size_t i = 0; i < n; ++i) {
            if (phi[i] != i)
                cerr << "\t" << i << " --> " << phi[i] << "\n";
        }
        cerr << "\n";

        changed = false;
        for (size_t v = 0; v < n; ++v) {
            if (!scanned[v] && outer(v, mu, phi)) {
                for (size_t v2: al[v]) {
                    if (outOfForest(v2, mu, phi) || (
                                outer(v2, mu, phi) && rho[v] != rho[v2])) {
                        if (outOfForest(v2, mu, phi)) {
                            phi[v2] = v;
                            changed = true;
                            cerr << "Grow(" << v << " -> " << v2 << ")\n";
        cerr << "Forest:\n";
        for (size_t i = 0; i < n; ++i) {
            if (phi[i] != i)
                cerr << "\t" << i << " --> " << phi[i] << "\n";
        }
                            continue;
                        }
                        vi pv = path(v, mu, phi);
                        vi pv2 = path(v2, mu, phi);
                        set<size_t> ss(all(pv));
                        ss.insert(all(pv2));
                        if (pv.size() + pv2.size() == ss.size()) {
                            cerr << "Augment (" << v << "<->" << v2 << ")\n";
                            for (size_t i = 1; i < pv.size(); i += 2) {
                                size_t v3 = pv[i];
                                mu[phi[v3]] = v3;
                                mu[v3] = phi[v3];
                            }
                            for (size_t i = 1; i < pv2.size(); i += 2) {
                                size_t v3 = pv2[i];
                                mu[phi[v3]] = v3;
                                mu[v3] = phi[v3];
                            }
                            mu[v2] = v;
                            mu[v] = v2;

                            for (size_t i = 0; i < n; ++i) {
                                phi[i] = rho[i] = i;
                                scanned[i] = false;
                            }
                            changed = true;
                            goto reset;
                        } else {
                            changed = true;
                            size_t r = first(pv, pv2);
                            phi[r] = r;
                            cerr << "Shrink: [";
                            for (size_t i = 0; i < pv.size(); ++i){
                                if (i)
                                    cerr << ", ";
                                cerr << pv[i];
                                if (pv[i] == r)
                                    break;
                            }
                            cerr << "] and [";
                            for (size_t i = 0; i < pv2.size(); ++i) {
                                if (i)
                                    cerr << ", ";
                                cerr << pv2[i];
                                if (pv2[i] == r)
                                    break;
                            }
                            cerr << "]\n";

                            for (size_t i = 1; i < pv.size(); i += 2) {
                                size_t v3 = pv[i];
                                if (rho[phi[v3]] != r) {
                                    phi[v3] = v3;
                                }
                                if (v3 == r)
                                    break;
                            }
                            for (size_t i = 1; i < pv2.size(); i += 2) {
                                size_t v3 = pv2[i];
                                if (rho[phi[v3]] != r) {
                                    phi[v3] = v3;
                                }
                                if (v3 == r)
                                    break;
                            }
                            if (phi[v] != r) {
                                phi[v] = v2;
                            }
                            if (phi[v2] != r) {
                                phi[v2] = v;
                            }
                            for (size_t i = 1; i < pv.size(); i += 2) {
                                size_t v3 = pv[i];
                                rho[v3] = r;
                                if (v3 == r)
                                    break;
                            }
                            for (size_t i = 1; i < pv2.size(); i += 2) {
                                size_t v3 = pv2[i];
                                rho[v3] = r;
                                if (v3 == r)
                                    break;
                            }
                        }
                    }
                }
            }
            scanned[v] = true;
        }
        reset:;

    } while(changed);

    {
        set<size_t> A;
        cerr << "Matching:\n";
        for (size_t i = 0; i < n; ++i) {
            if (mu[i] == i)
                continue;
            if (A.count(i))
                continue;
            cerr << "\t" << i << " <-> " << mu[i] << "\n";
            A.insert(mu[i]);
        }
    }

    return mu;
}

int main() {
    if (0) {
        vii al = {{3}, {2}, {3,1},{0,2}};
        debug(findMatching(al));
    }
    if (0) {
        vii al = {
            {1,4},
            {0,2},
            {1,3,5},
            {2,4},
            {0,3},
            {2,7,6},
            {5,7},
            {5,6}
        };
        debug(findMatching(al));
    }
    if (0) {
        vii al = {
            {1},
            {0,2},
            {1,3},
            {2,4},
            {3,5},
            {4,6},
            {5,7},
            {6}
        };
        debug(findMatching(al));
    }
    if (0) {
        vii al = {
            {1,3},
            {0,2,4},
            {1,5},
            {0,4,6},
            {1,3,5,7},
            {4,2,8},
            {3,7},
            {6,4,8},
            {7,5}
        };
        debug(findMatching(al));
    }
    if (0) {
        vii al = {
            {1,2},
            {0,2,3,4},
            {0,1,4,5},
            {1,4},
            {1,2,3,5},
            {2,4}
        };
        debug(findMatching(al));
    }
    if (1) {
        vii al = {
            {1,4},   // 0
            {0,2},   // 1
            {1,3,5}, // 2
            {2,4},   // 3
            {0,3, 8},// 4
            {2,7,6}, // 5
            {5,7},   // 6
            {5,6},   // 7
            {4,9,12},// 8
            {8,10},  // 9
            {9,11},  // 10
            {10,12}, // 11
            {8,11}   // 12
        };
        debug(findMatching(al));
    }

    return 0;
}
