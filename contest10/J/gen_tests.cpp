/* Team: moscow04 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <deque>
#include <queue>
#include <string>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>

#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

#define DEBUG

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)((a).size()))
#define pb push_back
#define MP make_pair
#define mp MP

#ifdef DEBUG
    #define debug(x) cerr << #x << ": " << (x) << endl;
#else
    #define debug(x) ;
#endif

typedef pair<int, int> pii;
typedef long long ll;

template <typename T> T sqr (T x) {return x * x;}
template <typename T> T abs (T x) {return x > 0 ? x : -x;}

template <typename T>
ostream & operator << (ostream & out, vector<T> const & a) {
    out << "[";
    for (int i = 0; i < sz(a); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << a[i];
    }
    out << "]";
    return out;
}

template <typename T1, typename T2>
ostream & operator << (ostream & out, pair<T1, T2> const & p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

void showTime () {
#ifdef DEBUG
    static double prev;
    static bool first = true;

    double curr = (double)clock() / CLOCKS_PER_SEC;

    cerr.setf(ios::fixed);
    cerr.precision(3);
    cerr << "<";
    if (!first) {
        cerr << curr - prev << "sec, ";
    }
    cerr << curr << "sec>\n";

    first = false;
    prev = curr;
#endif
}

ofstream inp("my_tests");
ofstream ans("my_answers");

void NoS() {
    ans << "No Solution\n";
}

void MulS() {
    ans << "Multiple Solutions\n";
}

void UniqS(const vector<int>& legs, const vector<int>& numbers) {
    ans << "Unique Solution\n";
    for (size_t i = 0; i < legs.size(); ++i) {
        ans << legs[i] << " " << numbers[i] << "\n";
    }
}

map<vector<int>, int> pos;
map<vector<int>, vector<int>> example;

int test;

void f(vector<int> a) {
    for (int w = 1; w < 40; ++w) {
        vector<int> b(a);
        vector<int> res;
        for (int it = 0; it <= w; ++it) {
            res.push_back(accumulate(all(b), 0));
            for (auto& x: b) {
                if (x)
                    --x;
            }
        }
        pos[res] += 1;
        example[res] = a;
    }
}

void go(vector<int>& a, int sum, int diff) {
    if (sum < 0 || diff <= 0)
        return ;
    if (sum == 0 && diff == 1) {
        f(a);
        return ;
    }
    if (a.empty()) {
        for (int i = 1; i <= sum; ++i) {
            a.push_back(i);
            go(a, sum - i, diff);
            a.pop_back();
        }
    } else {
        for (int i = a.back(); i <= sum; ++i) {
            int dec = int(i != a.back());
            a.push_back(i);
            go(a, sum - i, diff - dec);
            a.pop_back();
        }
    }
}

void outTestCase(vector<int> a, int diff) {
    inp << diff << " " << a.size() - 1 << "\n";
    for (auto x: a)
        inp << x << " ";
    inp << "\n";
}

void outAnswer(vector<int> a) {
    ++test;
    ans << "Case #" << test << ":\n";
    if (pos[a] == 0) {
        NoS();
    }
    if (pos[a] > 1) {
        MulS();
    }
    if (pos[a] == 1) {
        map<int, int> c;
        vector<int> r = example[a];
        for (size_t i = 0; i < r.size(); ++i)
            c[r[i]] += 1;
        vector<int> x, y;
        for (auto t: c)
            x.push_back(t.first), y.push_back(t.second);
        UniqS(x,y);
    }
}

void gen(int sum, int diff) {
    vector<int> a;
    go(a, sum, diff);
    for (auto it = pos.begin(); it != pos.end(); ++it) {
        outTestCase(it->first, diff);
        outAnswer(it->first);
    }
}

int main () {
    for (int sum = 1; sum < 20; ++sum) {
        for (int diff = 1; diff < 20; ++diff) {
            pos.clear();
            example.clear();
            gen(sum, diff);
        }
    }
    return 0;
}
