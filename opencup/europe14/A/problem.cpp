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

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {
   static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S> ostream& operator << (ostream& o, const pair<F, S>& p) {
   return o << "(" << p.first << ", " << p.second << ")";
}

template<class C>void O__(ostream& o, const C& c) {
   bool f = 1; for (const auto& x : c) { if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x; }
}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) { o << "["; O__(o, v); o << "]"; return o; }

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) { o << "{"; O__(o, v); o << "}"; return o; }

template <class T>
ostream& operator << (ostream& o, const set<T>& v) { o << "{"; O__(o, v); o << "}"; return o; }

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


int f[301][301][301];
struct alien {
   int a, b, d;
};

bool comp(const alien& a, const alien& b) {
   return a.b < b.b;

}

int main() {
    std::function<int(int)> fd;
    int *xxxx = new int(2);
   *xxxx = 3;
    cout << int(3.4);
   std::ios_base::sync_with_stdio(false);
   int t;
   cin >> t;
   for (int tt = 0; tt < t; ++tt) {
      int n;
      cin >> n;
      vector<alien> a(n);
      for (int i = 0; i < n; ++i) {
         cin >> a[i].a >> a[i].b >> a[i].d;
      }

      sort(a.begin(), a.end(), comp);

        vector<vector<int>> e(n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                if (a[i].b == a[j].b)
                    e[i].push_back(j);
            }
        debug(e);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                for (int k = j; k <= n; ++k) {
                    for (int t = 0; t < e[k-1].size(); ++t) {
                        int ind = e[k-1][t];
                        if (a[ind].a <= a[j-1].b/* && a[j-1].b <= a[ind].b*/)
                            f[i][j][k] = max(f[i][j][k-1], a[ind].d);
                    }
                }
            }
        }
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                for (int k = 0; k <= n; ++k)
                    cout << i << " " << j << " " << k << " " << f[i][j][k] << "\n";

      vector<vector<int> > d(n + 1, vector<int>(n + 1, INF));
      for (int i = 0; i < n + 1; ++i)
         d[i][i] = 0;
      for (int len = 1; len < n + 1; ++len) {
         for (int l = 0; l < n + 1; ++l) {
            int k = l + len;
            if (k > n)
               continue;
            for (int j = l + 1; j <= k; ++j)
               d[l][k] = min(d[l][k], d[l][j - 1] + d[j][k] + f[l][j][k]);
         }
      }
        cout << d[0][n] << "\n";
   }


   return 0;
}
