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
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

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

int dx[] = {-1,+1,0,0};
int dy[] = {0,0,-1,+1};

class SixteenBricks {
public:
    int res;
    int calc(const vii& a) {
        int cur = 16;
        for(int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int add = a[i][j] * 4;
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    if (nx < 0 || ny < 0 || nx == 4 || ny == 4)
                        continue;
                    add -= min(a[i][j], a[nx][ny]);
                }
                cur += add;
            }
        }
        return cur;
    }
    int maximumSurface(vector <int> height) {
        res = 16;
        while (1.0 * clock() / CLOCKS_PER_SEC < 0.5) {
            vii a(4, vi(4, 0));
            random_shuffle(all(height));
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    a[i][j] = height[i * 4 + j];
                }
            }

            while (1.0 * clock() / CLOCKS_PER_SEC < 0.5) {
                int it = 0;
                bool ok = 0;
                while (it < 100 && !ok) {
                    ++it;
                    int i = rand() % 4;
                    int j = rand() % 4;
                    for (int d = 0; !ok && d < 4; ++d) {
                        int nx = i + dx[d];
                        int ny = j + dy[d];
                        if (nx < 0 || ny < 0 || nx == 4 || ny == 4)
                            continue;
                        int c = calc(a);
                        swap(a[i][j], a[nx][ny]);
                        if (c < calc(a)) {
                           ok = 1;
                           break;
                        }
                        swap(a[i][j], a[nx][ny]);
                    }
                }
                res = max(res, calc(a));
                if (it == 100)
                    break;
            }
        }
        return res;
    }
    int so(vi a) {
        sort(all(a));
        vi b = {4,4,3,3,3,3,2,2};
        int r = 0;
        for (int i = 0; i < a.size(); ++i) {
            r += 4 * a[i];
            if (i < b.size())
                r -= 2 * b[i] * a[i];
        }
        return r;
    }
};

int main() {
    SixteenBricks t;
    debug(t.maximumSurface(vi(16,1)))
    /*while(true) {
        vi a;
        for (int i = 0; i < 16; ++i) {
            a.push_back(rand() % 50);
        }
        if (t.maximumSurface(a) > t.so(a)) {
            for (int i = 0; i < 16; ++i)
                cout << a[i] << ",";
            break;
        }
    }*/
    return 0;
}
