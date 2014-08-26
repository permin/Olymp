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
const long long LLINF = 1.5e14 + 0.5;

const int maxN = 60000;
int X[maxN];
int Y[maxN];
int T[maxN];
int P[maxN];
char killed[maxN];
ll dist[maxN];

inline int fastAbs(int x) {
    int sign= (x>>31);
    return (x^sign) - sign;
}
inline int fastMin(int a, int b) {
    return b + ((a-b) & (a-b)>>31);
}
inline int fastMax(int a, int b) {
    return a - ((a-b) & (a-b)>>31);
}
inline ll fastMin(ll a, ll b) {
    return b + ((a-b) & (a-b)>>63);
}

template<class T>
void pr(T a[maxN], int s) {
    cout << "{";
    for (int i = 0; i < s; ++i) {
        cout << (i?", ":"") << a[i];
    }
    cout << "}\n";
}

class JumpingOnPoints {
public:
    long long sumOfDistances(int N, int S, vector <int> params) {
        X[0] = params[0];
        Y[0] = params[4];
        P[0] = params[8];
        T[0] = params[12];
        for (int i = 1; i < N; i++) {
            X[i] = (1LL * X[i - 1] * params[1] + params[2]) % params[3];
            Y[i] = (1LL * Y[i - 1] * params[5] + params[6]) % params[7];
            P[i] = (1LL * P[i - 1] * params[9] + params[10]) % params[11];
            T[i] = (1LL * T[i - 1] * params[13] + params[14]) % params[15];
        }
        //pr(X, N);
        //pr(Y, N);
        //pr(P, N);
        //pr(T, N);
        std::list<int> interesting;
        for (int i = 0; i < N; ++i)
            interesting.push_back(i);
        for (int i = 0; i < N; ++i)
            dist[i] = i == S ? 0 : LLINF;
        for (int itt = 0; itt < N; ++itt) {
            auto best = interesting.end();
            for (auto it = interesting.begin(); it != interesting.end(); ++it) {
                if (best == interesting.end() || dist[*best] > dist[*it])
                    best = it;
            }
            int b = *best;
            if (dist[b] == LLINF)
                continue;
            interesting.erase(best);
            for (int i: interesting) {
                if (fastMin(fastAbs(X[b]-X[i]), fastAbs(Y[b]-Y[i])) <= P[b]) {
                    ll newDist = dist[b] + fastMax(T[b], T[i]);
                    dist[i] = fastMin(dist[i], newDist);
                }
            }
        }
        //pr(dist, N);
        ll res = 0;
        for (int i = 0; i < N; ++i) {
            res += dist[i];
        }
        return res;
    }
};

int main() {
    {
        JumpingOnPoints A;
        debug(A.sumOfDistances(3,1,
            {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
    }
    {
        JumpingOnPoints A;
        debug(A.sumOfDistances(
                    60000, 0,
                    {0, 1, 1, 1000000000, 0, 1, 1, 1000000000, 1, 1, 0, 1000000000, 999999999, 1, 0, 1000000000}));
    }
    debug(1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}
