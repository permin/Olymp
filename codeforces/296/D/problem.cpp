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
#include <complex>
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

template <>
ostream& operator << (ostream& o, const vector<char>& v) {
    o << "[";
    vector<int> v2;
    for (char x: v)
        v2.push_back(int(x));
    O__(o, v2);
    o << "]";
    return o;}

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

typedef complex<double> base;
typedef long long ll;

const int MAX = 19;

namespace FFT {
    int b[1 << MAX];
    double c[1 << MAX];
    double s[1 << MAX];
    void FFT(int n, base* a, bool inv = false) {
        static int x = -1;
        if (x != n) {
            for (int i = 0; i < 25; ++i) {
                c[i] = cos(2.0 * PI / (1 << i));
                s[i] = sin(2.0 * PI / (1 << i));
            }
            for (int i = 1, j = 0; i < n; ++i) {
                int bit = n >> 1;
                for (;j >= bit; bit >>= 1)
                    j -= bit;
                j += bit;
                b[i] = j;
            }
            x = n;
        }
        for (int i = 0; i < n; ++i)
            if (b[i] < i)
                swap(a[i], a[b[i]]);
        int p = 0;
        for (int len = 2; len <= n; len <<= 1) {
            ++p;
            base w1(c[p], inv ? -s[p] : s[p]);
            for (int i = 0; i < n; i += len) {
                base w(1);
                for (int j = 0; j < len/2; ++j) {
                    base u = a[i + j];
                    base v = a[i + j + len/2] * w;
                    a[i + j] = u + v;
                    a[i + j + len/2] = u - v;
                    w *= w1;
                }
            }
        }
        if (inv)
            for (int i = 0; i < n; ++i)
                a[i] /= n;
    }
} // FFT

vector<int> find1(const vector<char>&text, const vector<char>& pattern) {
    vector<base> t(1<<MAX);
    vector<base> p(1<<MAX);
    int sum = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        sum += int(pattern[i]);
    }

    for (int i = 0; i < text.size(); ++i) {
        t[i] = text[i];
    }
    for (int i = 0; i < pattern.size(); ++i) {
        p[i] = pattern[pattern.size() - 1 - i];
    }
    FFT::FFT(1 << MAX, t.data());
    FFT::FFT(1 << MAX, p.data());
    for (int i = 0; i < t.size(); ++i) {
        t[i] *= p[i];
    }
    FFT::FFT(1 << MAX, t.data(), true);
    vector<int> res;
    for (int i = 0; i < text.size(); ++i) {
        int x = int(t[i].real() + 0.5);
        if (x == sum) {
            res.push_back(i);
        }
    }
    return res;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    /*int n = 1 << 19;
    base* a = new base[n];
    vector<base> b;
    for (int i = 0; i < n; ++i) {
        a[i] = i % 1000;
        b.push_back(a[i]);
    }
    int d = int(a[222].real() + 0.5);
    FFT::FFT(n, b.data());
    FFT::FFT(n, b.data(), true);
    if (d == int(b[222].real() + 0.5))
       std::cout << "O";
    if (d == int(a[222].real() + 0.5))
       std::cout << "O";
    std::cerr << "--\n";
    std::cerr << double(clock())/CLOCKS_PER_SEC << " sec" << "\n";*/
    /*vector<char> text = {0,1,1,1,1,1};
    vector<char> pattern = {1,0,1};
    debug(find1(text, pattern));*/
    int _, k;
    cin >> _ >> _ >> k;
    string text, pattern;
    cin >> text >> pattern;

    int a,t,g,c;
    int l = 0;
    vector<char> a1(text.size());
    vector<char> a2, a3, a4;
    a2 = a3 = a4 = a1;
    a=t=g=c = 0;
    int r = 0;
    for (int i = 0; i < text.size(); ++i) {

        while(r < text.size() && r - i <= k) {
            if (text[r] == 'A')
                ++a;
            else if (text[r] == 'G')
                ++g;
            else if (text[r] == 'T')
                ++t;
            else if (text[r] == 'C')
                ++c;
            else {
                assert(false);
            }
            ++r;
        }

        if (i - l > k) {
            if (text[l] == 'A')
                --a;
            else if (text[l] == 'G')
                --g;
            else if (text[l] == 'T')
                --t;
            else if (text[l] == 'C')
                --c;
            else {
                assert(false);
            }
            ++l;
        }
        //std::cerr << i << " " << l << " " << r << "\n";


        assert(r - l <= 2 * k + 1);

        assert(a >= 0);
        assert(t >= 0);
        assert(g >= 0);
        assert(c >= 0);
        assert(a+t+g+c == r - l);
        if (a)
            a1[i] = 1;
        if (t)
            a2[i] = 1;
        if (g)
            a3[i] = 1;
        if (c)
            a4[i] = 1;
    }
    vector<char> p1(pattern.size());
    vector<char> p2;
    vector<char> p3;
    vector<char> p4;
    p2= p3 = p4 = p1;
    for (int i = 0; i < pattern.size(); ++i) {
        if (pattern[i] == 'A')
            p1[i] = 1;
        else if (pattern[i] == 'T')
            p2[i] = 1;
        else if (pattern[i] == 'G')
            p3[i] = 1;
        else if (pattern[i] == 'C')
            p4[i] = 1;
        else {
            assert(false);
        }
    }

    debug(a1);
    debug(p1);

    vi r1,r2,r3,r4;
    r1 = find1(a1,p1);
    r2 = find1(a2,p2);
    r3 = find1(a3,p3);
    r4 = find1(a4,p4);
    debug(r1);
    debug(r2);
    debug(r3);
    debug(r4);
    vi ans;
    std::set_intersection(all(r1), all(r2), std::back_inserter(ans));
    vi ans2;
    std::set_intersection(all(ans), all(r3), std::back_inserter(ans2));
    vi ans3;
    std::set_intersection(all(ans2), all(r4), std::back_inserter(ans3));
    std::cout << ans3.size() << "\n";
    return 0;
}

