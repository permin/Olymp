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


class PalindromeMatrix {
public:
    int bitCount(int n) {
        return n == 0 ? 0 : ((n&1)+bitCount(n>>1));
    }
    bool isSet(int mask, int i) {
        return mask & (1 << i);
    }
    int solve(int pos, int need, const vii& am, vii& dp) {
        if (pos < 0) {
            return need > 0 ? 1e9 : 0;
        }
        need = max(need, 0);
        int &res = dp[pos][need];
        if (res >= 0)
            return res;
        res = 1e9;
        for (int i = 0; i < 3; ++i) {
            res = min(res, am[pos][i] + solve(pos - 1, need - i, am, dp));
        }
        return res;
    }
    int minChange(vector <string> A, int rowCount, int columnCount) {
        int n = A.size();
        int m = A[0].size();
        int res = 1e9;
        for (int mask = 0; mask < (1 << m); ++mask) {
            if (bitCount(mask) < columnCount)
                continue;
            vector<vector<int> > am(n/2, vi(3, 1e9));
            for (int i = 0; i < (n/2); ++i) {
                const string& first = A[i];
                const string& second = A[n - 1 - i];
                vi bestPrices(3);
                //debug(i);
                for (int j = 0; j < m/2; ++j) {
                    vi curPrices(3, 1e9);
                    for (int values = 0; values < (1 << 4); ++values) {
                        int p = 0;
                        p += int (isSet(values, 0) == isSet(values, 1));
                        p += int (isSet(values, 2) == isSet(values, 3));
                        int cost = 0;
                        cost += (isSet(values, 0) != (first[j] == '1'));
                        cost += (isSet(values, 1) != (first[m - 1 - j] == '1'));
                        cost += (isSet(values, 2) != (second[j] == '1'));
                        cost += (isSet(values, 3) != (second[m - 1 - j] == '1'));
                        if (isSet(mask, j) && (isSet(values, 0) != isSet(values, 2)))
                            cost = 1e9;
                        if (isSet(mask, m - 1 - j) && (isSet(values, 1) != isSet(values, 3)))
                            cost = 1e9;
                        curPrices[p] = min(curPrices[p], cost);
                        //debug(values);
                        //debug(curPrices);
                    }
                    for (int k = 0; k < 3; ++k) {
                        bestPrices[k] += *std::min_element(curPrices.begin() + k, curPrices.end());
                        bestPrices[k] = min(bestPrices[k], int(1e9));
                    }
                }
                am[i] = bestPrices;
            }
            //debug(am);
            vector<vector<int>> dp(n/2, vi(rowCount + 1, -1));
            res = min(res, solve(n/2-1, rowCount, am, dp));
            if (res == 13) {
                //debug(mask);
                for (int i = 0; i < m; ++i)
                    cerr << isSet(mask, i);
                cerr << "\n";
                debug(am);
                debug(dp);
                exit(1);
            }

        }
        return res;
    }
};


class PalindromeMatrix2{
public:
    int bitCount(int n) {
        return n == 0 ? 0 : ((n&1)+bitCount(n>>1));
    }
    void doit(string first, string second, int mask, int sub,
            int* firstRes, int* secondRes, int* bothRes) {
        int firstCur = 0;
        int secondCur = 0;
        int bothCur = 0;
        int m = first.size();
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                if (first[i] != second[i]) {
                    ++bothCur;
                }
                if (sub & (1 << i)) {
                    first[i] = second[i];
                } else {
                    second[i] = first[i];
                }
            }
        }
        for (int i = 0; i + i < m; ++i) {
            if (mask & (1 << i)) {
                if (first[i] != first[m - 1 - i] && i + i < m)
                    firstCur += 2;
                if (second[i] != second[m - 1 - i] && i + i < m)
                    secondCur += 2;
            } else {
                if (first[i] != first[m - 1 - i] && i + i < m)
                    ++firstCur;
                if (second[i] != second[m - 1 - i] && i + i < m)
                    ++secondCur;
            }
        }
        *firstRes = firstCur;
        *secondRes = secondCur;
        *bothRes = bothCur;
    }
    int minChange(vector <string> A, int rowCount, int columnCount) {
        int n = A.size();
        int m = A[0].size();
        int res = 1e9;
        for (int mask = 0; mask < (1 << m); ++mask) {
            if (bitCount(mask) < columnCount)
                continue;
            vector<int> x(n, 1e9);
            vector<int> b(n / 2, 1e9);
            for (int i = 0; i + i < n; ++i) {
                for (int sub = mask; sub; sub = (sub - 1) & mask) {
                    int first, second, both;
                    doit(A[i], A[n - 1 - i], mask, sub, &first, &second, &both);
                    x[i] = min(x[i], first);
                    x[n - 1 - i] = min(x[n - i - 1], second);;
                    b[i] = both;
                }
                {
                    int first, second, both;
                    doit(A[i], A[n - 1 - i], mask, 0, &first, &second, &both);
                    x[i] = min(x[i], first);
                    x[n - 1 - i] = min(x[n - i - 1], second);
                    b[i] = both;
                }
            }
            sort(all(x));
            int cur = std::accumulate(all(b), 0);
            for (int i = 0; i < rowCount; ++i) {
                cur += x[i];
                cur = min(cur, int(1e9));
            }
            res = min(res, cur);
        }
        return res;
    }
};


#define TEST(...) debug(A.minChange(__VA_ARGS__))

int main() {
    PalindromeMatrix A;
    TEST({
            "0011",
            "0011",
            "1100",
            "1101"
        },
        4,4
    );
    TEST({"0000"
,"1000"
,"1100"
,"1110"},
2,
2);

    TEST({"0000"
,"1000"
,"1100"
,"1110"}, 3, 2);
    TEST({"01"
,"10"},
1,
1);
    TEST({"01"
,"10"},
2,
2);
    TEST({"1110"
,"0001"}, 0,0);
    TEST({"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"
,"01010101"},
2,
3);
    TEST({
 "000000000000"
,"011101110111"
,"010001010101"
,"010001010101"
,"011101010101"
,"010101010101"
,"010101010101"
,"011101110111"
,"000000000000"
,"000000000000"},
5,
9);
    TEST({"11111101001110"
,"11000111111111"
,"00010101111001"
,"10110000111111"
,"10000011010010"
,"10001101101101"
,"00101010000001"
,"10111010100100"
,"11010011110111"
,"11100010110110"
,"00100101010100"
,"01001011001000"
,"01010001111010"
,"10100000010011"},
6,
8);
    debug(1.0 * clock() / CLOCKS_PER_SEC);
    return 0;
}

 "000000000000"
,"011101110111"
  110011111011
,"010001010101"
,"011101110111"

,"010001010101"
,"011101010101"
,"010101010101"
,"010101010101"
,"000000000000"
,"000000000000"},
