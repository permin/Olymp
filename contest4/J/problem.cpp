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
const long long LLINF = std::numeric_limits<ll>::max() / 10;

const int N = 4001;
ll dp[N][N][2];

int starsNum;
int checkersNum;
int starPos[N];
int canSkipStar[N];
int checkerPos[N];
int correspondedStar[N];
int valueOfCorrespondedStar[N];
int directionOfCorrespondedStar[N];

ll solve(int i, int j, bool flag) {
    if (dp[i][j][flag] >= 0)
        return dp[i][j][flag];
    ll &res = dp[i][j][flag];
    res = LLINF;
    if (i == checkersNum && j == starsNum) {
        return res = 0;
    }
    if (i == checkersNum) {
        if (canSkipStar[j])
            return res = solve(i, j + 1, flag);
        else
            return res = LLINF;
    }
    if (j == starsNum) {
        return res = LLINF;
    }

    if (canSkipStar[j]) {
        res = min(res, solve(i, j + 1, flag));
    }

    if (j == correspondedStar[i]) {
        int add = valueOfCorrespondedStar[j];
        if (add == 1 && valueOfCorrespondedStar[i] == 1 && flag && i && correspondedStar[i - 1] != -1 && abs(starPos[correspondedStar[i - 1]] - starPos[correspondedStar[i]]) == 1 &&
                directionOfCorrespondedStar[i - 1] * directionOfCorrespondedStar[i] == -1) {
            add = 0;
        }
        res = min(res, add + solve(i + 1, j + 1, add));
    } else {
        if (abs(checkerPos[i] - starPos[j]))
            res = min(res, abs(checkerPos[i] - starPos[j]) + solve(i + 1, j + 1, 0));
    }
    return res;
}

int main() {
    memset(dp, -1, sizeof(dp));
    int n;
    cin >> n;
    vector<string> before(2);
    vector<string> after(2);
    cin >> before[0] >> before[1] >> after[0] >> after[1];

    vector<vector<int>> beforeId(2, vector<int> (n, -1));
    vector<vector<int>> afterId(2, vector<int> (n, -1));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (before[j][i] == 'o') {
                beforeId[j][i] = checkersNum++;
            }
            if (after[1][i] != '.') {
                afterId[1][i] = starsNum++;
            }
        }
    }
    for (int i = 0; i < checkersNum; ++i) {
        correspondedStar[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (beforeId[j][i] >= 0) {
                if (afterId[j ^ 1][i] >= 0) {
                    correspondedStar[beforeId[j][i]] = afterId[j^1][i];
                    valueOfCorrespondedStar[beforeId[j][i]] = 1;
                    directionOfCorrespondedStar[beforeId[j][i]] = j ? -1 : +1;
                }
                if (afterId[j][i] >= 0) {
                    correspondedStar[beforeId[j][i]] = afterId[j][i];
                    valueOfCorrespondedStar[beforeId[j][i]] = 0;
                    directionOfCorrespondedStar[beforeId[j][i]] = 0;
                }
            }
            if (beforeId[j][i] >= 0) {
                checkerPos[beforeId[j][i]] = i;
            }
            if (afterId[j][i] >= 0) {
                starPos[afterId[j][i]] = i;
                canSkipStar[afterId[j][i]] = after[j][i] == '*';
            }
        }
    }
    debug(starsNum);
    debug(checkersNum);
    debug(vector<int>(starPos, starPos + starsNum));
    debug(vector<int>(checkerPos, checkerPos + checkersNum));
    debug(vector<int>(correspondedStar, correspondedStar + checkersNum));
    debug(vector<int>(valueOfCorrespondedStar, valueOfCorrespondedStar+ checkersNum));
    debug(vector<int>(directionOfCorrespondedStar, directionOfCorrespondedStar+ checkersNum));
    cout << solve(0, 0, 0) << "\n";

    return 0;
}
