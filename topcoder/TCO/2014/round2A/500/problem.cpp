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

class NarrowPassage {
public:
    int minDist(int L, vector <int> a, vector <int> b) {
        vector<pii> c;
        for (int i = 0; i <a.size(); ++i)
            c.push_back(pii(a[i],b[i]));
        int n = a.size();
        sort(all(c));
        for (int i = 0; i < n; ++i) {
            a[i] = c[i].first;
            b[i] = c[i].second;
        }

        int res = INF;
        {
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j <= n; ++j) {
                    int cur = 0;
                    cur += std::accumulate(a.begin(), a.begin() + i, 0);
                    cur += (n - j) * L - std::accumulate(a.begin() + j, a.end(), 0);
                    cur += std::accumulate(b.begin(), b.begin() + i, 0);
                    cur += (n - j) * L - std::accumulate(b.begin() + j, b.end(), 0);
                    bool ok = 1;
                    if (i > 0 && *max_element(b.begin(), b.begin() + i) > *min_element(b.begin() + i, b.begin() + j))
                        ok = 0;
                    if (j != n && *min_element(b.begin() + j, b.end()) < *max_element(b.begin() + i, b.begin() + j))
                        ok = 0;
                    if (!is_sorted(b.begin() + i, b.begin() + j))
                        ok = 0;
                    for (int k = i; k < j; ++k)
                        cur += abs(a[k] - b[k]);
                    if (ok) {
                        res = min(res, cur);
                    }
                }
            }
        }
        {
            vector<pii> bOrder;
            for (int i = 0; i < n; ++i) {
                bOrder.push_back(pii(b[i], i));
            }
            sort(all(bOrder));

            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j <= n; ++j) {
                    int cur = 0;
                    cur += std::accumulate(a.begin(), a.begin() + i, 0);
                    cur += (n - i) * L - std::accumulate(a.begin() + i, a.end(), 0);
                    for (int k = 0; k < n; ++k) {
                        int index = bOrder[k].second;
                        if (k < j) {
                            if (index >= i) {
                                cur += L;
                            }
                            cur += bOrder[k].first;
                        } else {
                            if (index < i) {
                                cur += L;
                            }
                            cur += L - bOrder[k].first;
                        }
                    }
                    /*cur += accumulate(b.begin(), b.begin() + j, 0);
                    cur += (n - j) * L - accumulate(b.begin() + j, b.end(), 0);*/
                    res = min(res, cur);
                }
            }
        }
        return res;
    }
};


int main() {
    NarrowPassage A;
    debug(A.minDist(5, {1,2}, {3, 4}));
    debug(A.minDist(265467,
{133548, 103861, 29821, 199848, 92684, 219824, 215859, 62821, 172409, 109235,
38563, 148854, 24742, 174068, 205005, 75922, 87316, 5542, 57484, 40792,
25229, 152216, 21547, 22203, 84712, 231522, 235703, 184895, 100787, 174440,
156904, 84898, 185568, 108732, 260098, 89488, 221604, 104555, 165775, 90444,
81952, 149671, 209674, 22185, 45420, 41928, 16098, 65324, 90870, 35243},
{150289, 135139, 69841, 227226, 177427, 230314, 199175, 81572, 220468, 151049,
40009, 145963, 115246, 252932, 263651, 38434, 120096, 69576, 29789, 115046,
33310, 260771, 5723, 80733, 107864, 142447, 235490, 242149, 124564, 134602,
245962, 7078, 215816, 219864, 190499, 210237, 212894, 142760, 126472, 201935,
119308, 120211, 235235, 19446, 87314, 17286, 61990, 102050, 261812, 257}));
    debug("Returns: 7148670");
    debug(A.minDist(
1000000,
{706292, 756214, 490048, 228791, 567805, 353900, 640393, 562496, 217533, 934149,
938644, 127480, 777134, 999144, 41485, 544051, 417987, 767415, 971662, 959022,
670563, 34065, 518183, 750574, 546576, 207758, 159932, 429345, 670513, 271901,
476062, 392721, 774733, 502586, 915436, 120280, 951729, 699859, 581770, 268966,
79392, 888601, 378829, 350198, 939459, 644983, 605862, 721305, 269232, 137587},
{322468, 673534, 83223, 551733, 341310, 485064, 885415, 927526, 159402, 28144,
441619, 305530, 883149, 413745, 932694, 214862, 677401, 104356, 836580, 300580,
409942, 748444, 744205, 119051, 999286, 462508, 984346, 887773, 856655, 245559,
418763, 840266, 999775, 962927, 779570, 488394, 760591, 326325, 206948, 13999,
285467, 401562, 786209, 169847, 171326, 2901, 296531, 572035, 364920, 939046}));
    debug("Returns: 45670501");
    return 0;
}
