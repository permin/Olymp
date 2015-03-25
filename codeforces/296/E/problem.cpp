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

class FenwickTree {
public:
	// Using signed type for index allows some methods to be written briefly
	typedef int Index;

    explicit FenwickTree(Index size)
        : sums_(size, 0)
    {}

    // Takes O(vector size) time to perform
    void initialize(std::vector<int> numbers) {
        // Thanks to someone for this simple idea
        std::partial_sum(numbers.begin(), numbers.end(), numbers.begin());
        sums_.resize(numbers.size());
        for (Index i = 0; i < size(); ++i) {
            sums_[i] = numbers[i];
            Index previousI = previousIndex(i);
            if (previousI > 0) {
                sums_[i] -= numbers[previousI - 1];
            }
        }
    }

    void add(Index index, int value) {
        while (index < size()) {
            sums_[index] += value;
            index |= (index + 1);
        }
    }

    int sum(Index firstIndex, Index lastIndex) const {
        return sum(lastIndex) - sum(firstIndex - 1);
    }

    int at(Index index) const {
        return sum(index, index);
    }

    Index size() const {
        return static_cast<Index>(sums_.size());
    }

private:
    int sum(Index lastIndex) const {
        return lastIndex >= 0
            ? sums_.at(lastIndex) + sum(previousIndex(lastIndex) - 1)
            : 0;
    }

    // Given i, returns i' equal to i in binary notation
    // with all trailing one bits replaced by zeros
    static Index previousIndex(Index index) {
        return index & (index + 1);
    }

    std::vector<int> sums_;
};



double norm1(double a) {
    while(a >= PI / 2)
        a -= PI;
    while(a < -PI/2)
        a += PI;
    return a;
}

double det2(double a, double b, double c, double d) {
    return a * d - b * c;
}

pdd intersect(double a, double b, double c, double A, double B, double C) {
    double d = det2(a, b, A, B);
    return pdd(det2(-c, b, -C, B) / d,
               det2(a, -c, A, -C) / d);
}

double area(const pdd& A, const pdd& B, const pdd& C) {
    return 0.5 * (
            det2(B.first, B.second, C.first, C.second) -
            det2(A.first, A.second, C.first, C.second) +
            det2(A.first, A.second, B.first, B.second));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<double> a(n);
    vector<double> b(n);
    vector<double> c(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i] >> c[i];

    vector<double> alpha1(n);
    for (int i = 0; i < n; ++i) {
        alpha1[i] = norm1(atan2(a[i], -b[i]));
    }

    {
        auto te = alpha1;
        sort(all(te));
        for (int i =0; i + 1 < n; ++i) {
            assert(fabs(te[i + 1] - te[i]) > EPS);
        }
    }

    double ans = 0.0;
    for (int i = 0; i < n; ++i) {
        vector<pair<pdd, int>> p;
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                p.push_back(make_pair(intersect(a[i],b[i],c[i],a[j],b[j],c[j]), j));
            }
        }
        sort(all(p));
        vector<double> x;
        for (int j = 0; j < n - 1; ++j) {
            double my = alpha1[i];
            double ot = alpha1[p[j].second];
            if (ot > my) {
                x.push_back(ot - my);
            } else {
                x.push_back(PI + (ot - my));
            }
        }

        vi yWin(n - 1);
        vi yLose(n - 1);
        {
            vi p(x.size());
            for (int k = 0; k < x.size(); ++k) {
                p[k] = k;
            }
            sort(all(p), [&](int i, int j) {
                return x[i] < x[j];
            });
            {
                FenwickTree tree(n - 1);
                for (int k: p) {
                    yWin[k] = tree.sum(0, k);
                    tree.add(k, 1);
                }
            }

            reverse(all(p));

            {
                FenwickTree tree(n - 1);
                for (int k: p) {
                    yLose[k] = tree.sum(k, n - 2);
                    tree.add(k, 1);
                }
            }
        }

        int good = 0;
        for (int j = 1; j < x.size(); ++j) {
            if (x[j] > x[0])
                ++good;
        }
        for (int j = 0; j + 1 < x.size(); ++j) {
            if (j) {
                good -= yWin[j];
                good += yLose[j];
            }
            double curArea = area(p[j].first, p[j + 1].first, pdd(0.0, 0.0));
            double mul = 2 * good - (j + 1) * (n - 2 - j);
            ans += mul * curArea;
        }
        /*for (int j = 0; j + 1 < x.size(); ++j) {
            double curArea = area(p[j].first, p[j + 1].first, pdd(0.0, 0.0));
            double mul = 0.0;
            for (int y = 0; y <= j; ++y) {
                for (int z = j + 1; z < x.size(); ++z) {
                    if (x[y] < x[z])
                        ++mul;
                    else
                        --mul;
                }
            }
            ans += curArea * mul;
        }*/
    }
    ans /= n;
    ans /= n - 1;
    ans /= n - 2;
    ans *= 6.0;
    std::cout << ans << "\n";
    return 0;

    double correct = 0.0;
    {
        double num = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                for (int k = 0; k < j; ++k) {
                    correct += fabs(
                            area(intersect(a[i],b[i],c[i],a[j],b[j],c[j]),
                                 intersect(a[i],b[i],c[i],a[k],b[k],c[k]),
                                 intersect(a[k],b[k],c[k],a[j],b[j],c[j])));
                    num += 1;
                }
            }
        }
        correct /= num;
    }
    std::cerr << correct << "\n";

}
