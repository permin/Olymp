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
const long long LLINF = std::numeric_limits<ll>::max();

int ddd[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date {
    int day;
    int month;
    int year;
    bool operator==(const Date& d) {
        return day == d.day && month == d.month && year == d.year;
    }
};

bool isLeap(int y) {
    if (y % 400 == 0) {
        return 1;
    } else if (y % 100) {
        return 0;
    } else if (y % 4){
        return 1;
    } else {
        return 0;
    }
}

Date tommorow(Date d) {
    ++d.day;
    int dpm = ddd[d.month];
    if (d.month == 2 && isLeap(d.year))
        ++dpm;
    if (d.day > dpm){
        d.day = 1;
        d.month += 1;
    }
    if (d.month == 13) {
        d.month = 1;
        d.year += 1;
    }
    return d;
}

struct Time {
    int h, m;
};

Time inc(Time t, int minutes) {
    t.m += minutes;
    t.h += t.m / 60;
    t.m %= 60;
    return t;
}

struct DateTime {
    Date d;
    Time t;
};

DateTime inc(DateTime dt, int minutes) {
    dt.t = inc(dt.t, minutes);
    while (dt.t.h >= 24) {
        dt.t.h -= 24;
        dt.d = tommorow(dt.d);
    }
    return dt;
}

bool operator<(const Time& a,const Time& b) {
    return make_pair(a.h, a.m) <
           make_pair(b.h, b.m);
}

bool areClose(DateTime a, DateTime b) {
    if (a.d == b.d) {
        return 1;
    }
    if (b.d == tommorow(a.d)) {
        return b.t < a.t;
    }
    return 0;
}

DateTime read() {
    string a, b;
    cin >> a >> b;
    DateTime dt;
    dt.d.year = 1000 * (a[0] - '0') +
                100 * (a[1] - '0') +
                10 * (a[2] - '0') +
                (a[3] - '0');
    dt.d.month = 10 * (a[5] - '0') + (a[6] - '0');
    dt.d.day = 10 * (a[8] - '0') + (a[9] - '0');

    dt.t.h = 10 * (b[0] - '0') + (b[1] - '0');
    dt.t.m = 10 * (b[3] - '0') + (b[4] - '0');
    return dt;
}

int main() {
    int t;
    cin >> t;
    while(t-->0) {
        map<pair<string, string>, DateTime> endCall;
        map<string, set<string>> res;
        int n;
        cin >> n;
        while(n-->0) {
            DateTime dt = read();
            int d;
            cin >> d;
            string from ,to;
            cin >> from >> to;
            res[from];
            res[to];
            endCall[make_pair(from, to)] = inc(dt, d);
            if (endCall.count(make_pair(to, from))) {
                if (areClose(endCall[make_pair(to, from)], dt)) {
                    res[to].insert(from);
                    res[from].insert(to);
                }
            }
        }
        for (const auto& x: res) {
            cout << x.first << ": ";
            for (const auto& y: x.second) {
                cout << y << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
