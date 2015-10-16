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

#if GCC_VERSION > 40900
using namespace __gnu_pbds;
#endif
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
typedef vector<ll> vll;
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

void gauss(vll& data) {
    int k = 0;
    for (int i = 32; i >= 0; --i) {
        int f = -1;
        for (int j = k; j < (int)data.size(); ++j) {
            if ((1LL << i) & data[j]) {
                f = j;
                break;
            }
        }
        if (f == -1)
            continue;
        swap(data[f], data[k]);
        for (int j = k + 1; j < (int)data.size(); ++j) {
            if ((1LL << i) & data[j]) {
                data[j] ^= data[k];
            } else {
            }
        }
        ++k;
    }
    data.resize(k);
}

const int B = 1000;
vector<ll> seq;
int n;
vector<vll> blockGauss;
vector<int> blockDelay;
int blocksNum;

static vll data;

void recalcBlock(int b) {
    int l = b * B;
    int r = min(n, b * B + B);
    for (int i = l; i < r; ++i) {
        seq[i] ^= blockDelay[b];
    }
    blockDelay[b] = 0;
    data.clear();
    for (int i = l; i < r ; ++i) {
        data.push_back(1 + 2 * seq[i]);
    }
    gauss(data);
    blockGauss[b] = std::move(data);
}

void recalc() {
    for (int i = 0; i < blocksNum; ++i) {
        recalcBlock(i);
    }
}

size_t rk(int l, int r) {
    if (r - l <= B) {
        data.clear();
        for (int i = l; i <= r; ++i) {
            data.push_back(seq[i] ^ blockDelay[i/B]);
        }
        gauss(data);
        return data.size();
    } else {
        data.clear();
        while(l % B) {
            data.push_back(seq[l] ^ blockDelay[l/B]);
            ++l;
        }
        while(r % B) {
            data.push_back(seq[r] ^ blockDelay[r/B]);
            --r;
        }
        data.push_back(seq[r] ^ blockDelay[r/B]);
        --r;
        int b1 = l/B;
        int b2 = r/B;
        for (int b = b1; b <= b2; ++b) {
            for (ll x: blockGauss[b]) {
                if (x & 1LL) {
                    data.push_back((x/2) ^ blockDelay[b]);
                } else {
                    data.push_back((x/2));
                }
            }
        }
        gauss(data);
        return data.size();
    }
}

void upd(int l, int r, ll x) {
    if (r - l <= B) {
        for (int i = l; i <= r; ++i) {
            seq[i] ^= x;
        }
        int b1 = l/B;
        int b2 = r/B;
        for (int b = b1; b <= b2; ++b) {
            recalcBlock(b);
        }
    } else {
        int b3= -1;
        while(l % B) {
            seq[l] ^= x;
            b3=l/B;
            ++l;
        }
        if (b3 != -1) {
            recalcBlock(b3);
        }
        b3=-1;
        while(r % B) {
            seq[r] ^= x;
            b3=r/B;
            --r;
        }
        if (b3 != -1) {
            recalcBlock(b3);
        }
        seq[r] ^= x;
        --r;
        int b1 = l/B;
        int b2 = r/B;

        for (int b = b1; b <= b2; ++b) {
            blockDelay[b] ^= x;
        }
    }
}

string p2[40];

string add(string x, string y) {
    string z(x.size(), '?');
    char c = 0;
    int n = (int)x.size();
    for (int i = n - 1; i >= 0; --i) {
        z[i] = '0' + (char(c + (x[i] - '0') + (y[i] - '0'))%10);
        c = char(c + (x[i] - '0') + (y[i] - '0')) / 10;
    }
    if (c) {
        z = "1" + z;
    }
    return z;
}

int main() {
    data.reserve(1000);
    for (int i = 0; i <= 35; ++i) {
        p2[i] = (i==0)?"1":add(p2[i-1],p2[i-1]);
    }
    std::ios_base::sync_with_stdio(false);
    cin >> n;
    int q;cin >> q;

    seq.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> seq[i];
    }
    blocksNum = (n+B-1)/B;
    blockDelay.resize(blocksNum);
    blockGauss.resize(blocksNum);
    recalc();

    vll ans;
    while(q-->0) {
        if (q % 1000 == 0)
            cerr << q << " ";
        int t;
        cin >> t;
        if (t == 1) {
            int l,r;
            ll x;
            cin >> l >> r >> x;
            --l;--r;
            upd(l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            --l;--r;
            ans.push_back(rk(l,r));
        }
    }
    for (ll x: ans) {
        cout << p2[x] << "\n";
    }

    return 0;
}
