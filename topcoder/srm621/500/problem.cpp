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

class TreesAnalysis{
public:
    vii buildAl(const vi& a) {
        vii al(a.size() + 1);
        for (int i = 0; i < a.size(); ++i) {
            al[i].push_back(a[i]);
            al[a[i]].push_back(i);
        }
        return al;
    }
    void dfs(int v, int p, const vii& al, vi& s, vi& par) {
        par[v] = p;
        s[v] = 1;
        for (int i = 0; i < al[v].size(); ++i) {
            int v2 = al[v][i];
            if (v2 == p)
                continue;
            dfs(v2, v, al, s, par);
            s[v] += s[v2];
        }
    }
    int calc(int i, int j, const vii& firstAl, const vii& secondAl, vii& U,
            const vector<vector<bool>>& inSubTreeFirst,
            const vector<vector<bool>>& inSubTreeSecond) {
        int &res = U[i][j];
        if (res >= 0)
            return res;
        res = 0;
        res += inSubTreeFirst[i][j];
        if (i != j)
            res += inSubTreeSecond[j][i];
        for (auto v1: firstAl[i])
            for (auto v2: secondAl[j]) {
                if (inSubTreeFirst[i][v1] && inSubTreeSecond[j][v2]) {
                    res += calc(v1, v2, firstAl, secondAl, U, inSubTreeFirst, inSubTreeSecond);
                }
            }
        return res;
    }
    ll sqr(int x) {
        return 1LL * x * x;
    }
    long long treeSimilarity(vector <int> tree1, vector <int> tree2) {
        vii firstAl = buildAl(tree1);
        vii secondAl = buildAl(tree2);
        int n = tree1.size() + 1;
        vi firstSub(n);
        vi secondSub(n);
        vi p1(n);
        vi p2(n);
        dfs(0, -1, firstAl, firstSub, p1);
        dfs(0, -1, secondAl, secondSub, p2);
        vector<vector<bool>> inSubTreeFirst(n, vector<bool>(n, false));
        vector<vector<bool>> inSubTreeSecond(n, vector<bool>(n, false));
        for (int i = 0; i < n; ++i) {
            {
                int v=  i;
                while (v >= 0) {
                    inSubTreeFirst[v][i] = 1;
                    v = p1[v];
                }
            }
            {
                int v= i;
                while (v >= 0) {
                    inSubTreeSecond[v][i] = 1;
                    v = p2[v];
                }
            }
        }
        //debug(p1);
        //debug(inSubTreeFirst);
        //debug(p2);
        //debug(inSubTreeSecond);
        vii U(n, vi(n, -1));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                calc(i, j, firstAl, secondAl, U, inSubTreeFirst, inSubTreeSecond);
        ll res = 0;
        //debug(firstSub);
        //debug(secondSub);
        //debug(U);
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                int a = U[i][j];
                int b = secondSub[j] - a;
                int c = firstSub[i] - a;
                assert(b >= 0);
                assert(c >= 0);
                int d = n - a - b - c;
                assert(d >= 0);
                int s = max(max(a,b),max(c,d));
                //cerr << i << " " << j << " " << s << "\n";
                res += sqr(s);
            }
        }
        return res;
    }
};


int main() {
    TreesAnalysis A;
    debug(A.treeSimilarity({1},{1}));
    debug(A.treeSimilarity({2, 4, 1, 0},{ 1, 4, 4, 4}));
    debug(A.treeSimilarity({2, 3, 4, 4, 5, 8, 5, 6, 10, 8},
{9, 0, 1, 0, 3, 0, 5, 0, 7, 10}));
    debug(A.treeSimilarity({222, 261, 167, 133, 174, 150, 165, 311, 208, 268, 111, 222, 154, 277, 282, 201, 46, 124, 194, 331, 4, 216, 111,
275, 72, 322, 137, 216, 241, 48, 72, 101, 232, 165, 151, 263, 139, 16, 122, 140, 84, 135, 314, 106, 309, 126, 102,
151, 208, 27, 242, 93, 83, 314, 136, 77, 82, 215, 16, 232, 286, 156, 294, 38, 67, 204, 206, 137, 174, 282, 188,
143, 84, 279, 236, 136, 158, 10, 65, 332, 122, 44, 329, 62, 174, 67, 102, 216, 245, 296, 287, 307, 93, 197, 169,
268, 266, 294, 157, 277, 95, 68, 214, 135, 211, 127, 82, 108, 212, 161, 243, 212, 207, 119, 119, 158, 97, 290, 21,
217, 230, 85, 171, 13, 138, 294, 304, 204, 318, 115, 70, 210, 195, 223, 37, 164, 149, 3, 164, 328, 316, 108, 330,
48, 38, 324, 222, 193, 50, 41, 184, 93, 148, 41, 151, 139, 106, 301, 264, 80, 249, 110, 244, 109, 212, 223, 279,
330, 67, 27, 301, 165, 236, 194, 3, 157, 1, 217, 311, 87, 105, 4, 286, 37, 6, 31, 111, 66, 230, 227, 244, 322,
196, 65, 69, 305, 112, 133, 231, 68, 153, 206, 309, 248, 329, 58, 69, 69, 328, 0, 29, 233, 243, 305, 167, 80, 65,
194, 190, 179, 142, 196, 324, 206, 134, 50, 272, 261, 10, 147, 329, 322, 14, 142, 169, 21, 296, 284, 241, 55, 304,
150, 166, 230, 167, 304, 87, 156, 156, 97, 274, 324, 196, 101, 82, 106, 260, 242, 233, 207, 305, 10, 166, 53, 18,
154, 233, 217, 296, 263, 168, 138, 30, 115, 135, 188, 98, 309, 292, 204, 150, 210, 332, 330, 166, 96, 70, 24, 229,
215, 201, 285, 40, 287, 142, 68, 133, 208, 268, 161, 310, 41, 203, 73, 275, 184, 163, 227, 89, 110, 328, 108, 112,
125, 164, 127, 179, 267, 221, 49, 139, 1, 84, 136, 38, 6, 70, 246, 243, 3, 188, 297},
{174, 262, 195, 288, 157, 278, 36, 133, 230, 273, 222, 138, 97, 23, 189, 141, 296, 55, 45, 301, 81, 199, 188, 289,
187, 164, 113, 58, 138, 300, 289, 282, 329, 91, 130, 178, 92, 143, 48, 81, 311, 133, 151, 286, 171, 196, 199, 80,
83, 121, 65, 151, 277, 136, 49, 111, 58, 36, 259, 14, 31, 9, 136, 181, 122, 324, 249, 114, 9, 37, 259, 242, 165,
174, 34, 36, 298, 92, 301, 237, 178, 82, 65, 295, 110, 311, 274, 235, 68, 56, 259, 180, 195, 52, 110, 68, 140, 71,
52, 296, 290, 115, 213, 82, 209, 209, 74, 178, 302, 131, 99, 205, 296, 309, 288, 180, 329, 71, 143, 58, 152, 273,
196, 7, 169, 88, 231, 331, 213, 181, 80, 249, 170, 246, 16, 127, 75, 276, 332, 174, 21, 180, 163, 78, 242, 312,
295, 199, 89, 142, 85, 195, 115, 119, 95, 94, 279, 290, 3, 33, 93, 284, 20, 47, 47, 78, 331, 271, 113, 179, 249,
331, 92, 324, 9, 71, 232, 46, 28, 289, 80, 28, 80, 134, 20, 280, 277, 48, 205, 107, 52, 320, 4, 191, 160, 182,
189, 227, 295, 115, 54, 195, 78, 292, 189, 273, 301, 69, 305, 36, 222, 167, 326, 106, 48, 45, 74, 61, 181, 311,
292, 270, 201, 34, 314, 218, 214, 92, 269, 18, 37, 151, 142, 209, 11, 227, 327, 198, 28, 272, 152, 22, 47, 143,
332, 253, 273, 35, 78, 130, 295, 223, 181, 329, 18, 238, 300, 186, 274, 99, 300, 322, 41, 185, 311, 288, 198, 2,
37, 83, 238, 133, 122, 178, 107, 106, 66, 238, 69, 90, 38, 109, 246, 278, 288, 250, 321, 269, 130, 28, 115, 122,
33, 185, 275, 99, 130, 99, 152, 268, 133, 249, 180, 30, 210, 201, 324, 29, 290, 143, 3, 269, 68, 106, 230, 1,
269, 29, 120, 259, 324, 328, 23, 243, 9, 61, 14, 118, 199, 146, 237, 14}));
    return 0;
}
