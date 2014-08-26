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

template<int bits>
struct Bit21Array {
    int get(int i) const {
        int pos = i * 21;
        int res = 0;
        for (int j = pos; j < pos + 21; ++j) {
            res = (res << 1) + data[j];
        }
        return res;
    }
    void set(int i, int value) {
        int pos = i * 21;
        for (int j = pos; j < pos + 21; ++j) {
            int k = 20 - (j - pos);
            data[j] = (value >> k) & 1;
        }
    }
    bitset<bits> data;
};

int main() {
    int n;
    cin >> n;
    Bit21Array<21 * 2 * 1000 * 1000> childs;
    Bit21Array<21 * 1000 * 1000> st;
    int stackHead = 0;

    for (int i = 0; i < n; ++i) {
        int a,b;
        cin >> a >> b;
        childs.set(2 * i, a);
        childs.set(2 * i + 1, b);
    }

    st.set(stackHead++, 0);
    int mark = 1 << 20;

    cout << "DFS\n";

    while (stackHead) {
        int vertex = st.get(stackHead - 1)  & ((1 << 20) - 1);
        int left = childs.get(vertex * 2);
        int right = childs.get(vertex * 2 + 1);
        if (st.get(stackHead - 1) & mark) {
            int res = 1;
            if (left) {
                --left;
                res += childs.get(left * 2);
            }
            if (right) {
                --right;
                res += childs.get(right * 2);
            }
            childs.set(vertex * 2, res);
            childs.set(vertex * 2 + 1, 0);
            st.set(stackHead - 1, 0);
            --stackHead;
        } else {
            cout << vertex + 1 << "\n";
            st.set(stackHead - 1, vertex | mark);
            if (right) {
                st.set(stackHead++, right - 1);
            }
            if (left) {
                st.set(stackHead++, left - 1);
            }
        }
    }
    ll sum = 0;
    for (int i = 1; i < n; ++i) {
        sum += childs.get(i + i);
    }
    cout << sum << "\n";


    return 0;
}

