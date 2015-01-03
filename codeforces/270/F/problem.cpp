#include <iostream>
#include <cstdlib>
#include <cstdio>
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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;};

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x;}}

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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

ll sqr(int x) {
    return 1LL * x * x;
}

struct State {
    //vector<vi> plan;
    vector<vi> plan;
    int i, j;
    bool operator<(const State& s) const {
        return t() < s.t();
    }
    tuple<vector<vi>, int, int> t() const {
        return make_tuple(plan, i, j);
    }
};

int XS[900];
int YS[900];

int curCX[900];
int curCY[900];

int STEP;
State global;
ll globalScore;

ll score(const State& x, int step);

int CCCC;
const int MAXCCCC = 1000*1000*10;

vector<pii> path;
vector<pii> tmp;

void dfs(State& s, ll curScore, int d) {
    /*ll SC = score(s, STEP);
    if (SC > score(global, STEP) + 2000) {
        if (rand() & 1)
            return;
    }*/
    ++CCCC;
    if (CCCC > MAXCCCC)
        return;
    //if (curScore > globalScore ) {
        //if (CCCC % 3 == 0)
        //    return;
    //}
    //debug(STEP);
    //debug(s.plan);
    //debug(curScore);
    //debug(score(s,STEP));
    //assert(curScore == score(s, STEP));
    if (curScore < globalScore) {
        path = tmp;
        globalScore = curScore;
        global = s;
    }
    if (d == 0)
        return;
    for (int dx = -1; dx <= +1; ++dx)
        for (int dy = -1; dy <= +1; ++dy) {
            if (dx == 0 && dy == 0)
                continue;
            int ox = s.i;
            int oy = s.j;
            int x = s.i + dx;
            int y = s.j + dy;
            if (x < 0 || y < 0 || x >= s.plan.size() || y >= s.plan[0].size()) {
                continue;
            }

            //debug(STEP);
            //debug(s.plan);
            //debug(curScore);
            //debug(score(s,STEP));
            //assert(curScore == score(s, STEP));

            ll oldCurScore = curScore;
            int first = s.plan[ox][oy];
            int second = s.plan[x][y];
            //debug(first);
            //assert(s.plan[curCX[first]][curCY[first]] == first);
            //assert(s.plan[curCX[second]][curCY[second]] == second);

            //debug(curScore);
            if (first < STEP) {
                curScore -= 1000 * (sqr(XS[first] - curCX[first]) + sqr(YS[first] - curCY[first]) );
            }
            if (first == STEP) {
                curScore -= 10000 * (sqr(XS[first] - curCX[first]) + sqr(YS[first] - curCY[first]) );
            }
            //std::cerr << "Remove " << first << " " << curScore << "\n";
            //debug(curScore);
            if (second < STEP) {
                curScore -= 1000 * (sqr(XS[second] - curCX[second]) + sqr(YS[second] - curCY[second]) );
            }
            if (second == STEP) {
                curScore -= 10000 * (sqr(XS[second] - curCX[second]) + sqr(YS[second] - curCY[second]) );
            }
            //std::cerr << "Remove " << second << " " << curScore << "\n";

            if (STEP < s.plan.size() * s.plan[0].size()) {
                /*debug(s.plan);
                debug(STEP);
                debug(curCX[STEP]);
                debug(curCY[STEP]);
                debug(s.i);
                debug(s.j);*/
                curScore -= sqr(curCX[STEP] - s.i);
                curScore -= sqr(curCY[STEP] - s.j);
            }
            //std::cerr << "Remove addition" << " " << curScore << "\n";

            //debug(curScore);
            //assert(curScore % 1000 == 0);
            tmp.push_back(pii(x,y));

            swap(s.plan[ox][oy], s.plan[x][y]);
            curCX[first] = x;
            curCY[first] = y;
            curCX[second] = ox;
            curCY[second] = oy;
            //assert(s.plan[curCX[first]][curCY[first]] == first);
            //assert(s.plan[curCX[second]][curCY[second]] == second);

            if (first < STEP) {
                curScore += 1000 * (sqr(XS[first] - curCX[first]) + sqr(YS[first] - curCY[first]));
            }
            if (first == STEP) {
                curScore += 10000 * (sqr(XS[first] - curCX[first]) + sqr(YS[first] - curCY[first]));
            }
            //std::cerr << "Add" << first << " " << curScore << "\n";
            if (second < STEP) {
                curScore += 1000 * (sqr(XS[second] - curCX[second]) + sqr(YS[second] - curCY[second]));
            }
            if (second == STEP) {
                curScore += 10000 * (sqr(XS[second] - curCX[second]) + sqr(YS[second] - curCY[second])) ;
            }
            //std::cerr << "Add" << second << " " << curScore << "\n";

            if (STEP < s.plan.size() * s.plan[0].size()) {
                curScore += sqr(curCX[STEP] - x);
                curScore += sqr(curCY[STEP] - y);
            }
            //std::cerr << "Add" << " addition"<< " " << curScore << "\n";

            s.i = x;
            s.j = y;
            //assert(s.plan[curCX[first]][curCY[first]] == first);
            //assert(s.plan[curCX[second]][curCY[second]] == second);
            dfs(s, curScore, d - 1);
            tmp.pop_back();
            swap(s.plan[ox][oy], s.plan[x][y]);
            curCX[first] = ox;
            curCY[first] = oy;
            curCX[second] = x;
            curCY[second] = y;
            s.i = ox;
            s.j = oy;
            //assert(s.plan[curCX[first]][curCY[first]] == first);
            //assert(s.plan[curCX[second]][curCY[second]] == second);

            curScore = oldCurScore;
        }
}

ll score(const State& x, int step) {
    vector<pii> a(x.plan.size() * x.plan[0].size());
    for (int i = 0; i < x.plan.size(); ++i) {
        for (int j = 0; j < x.plan[0].size(); ++j) {
            a[x.plan[i][j]] = pii(i,j);
        }
    }
//dd
    ll res = 0;
    for (int i = 0; i <= step && i < a.size();++i) {
        int X = XS[i];
        int Y = YS[i];
        ll cur = sqr(X - a[i].first) + sqr(Y - a[i].second) ;
        if (i < step) {
            res += cur;
        }
        if (i == step) {
            res += 10*cur;
        }
    }
    res *= 1000;
    if (step<a.size()){
        res += sqr(a[step].first - x.i);
        res += sqr(a[step].second - x.j);
    }
    //assert(res >= 0);
    return res;
}

bool go(State x, vector<pii>& res) {
    res.clear();
    res.push_back(pii(x.i, x.j));
    int step = 0;
    while (step != x.plan.size() * x.plan[0].size()) {
        //debug(x.plan);
        while (step < x.plan.size() * x.plan[0].size()) {
            int X = XS[step];
            int Y = YS[step];
            if (x.plan[X][Y] == step) {
                ++step;
            } else {
                break;
            }
        }
        if (step == x.plan.size() * x.plan[0].size())
            break;
        //debug(step);
        global = x;
        globalScore = score(global, step);
        STEP = step;
        int de = 3;
        while (!(x < global || global < x)) {
            dfs(x, globalScore, de);
            if (CCCC > MAXCCCC)
                return 0;
            //debug(de);
            de += 1;
        }
        for (int i = 0; i < path.size(); ++i)
            res.push_back(path[i]);
        x = global;
        for (int i = 0; i < x.plan.size(); ++i)
            for (int j = 0; j < x.plan[0].size(); ++j) {
                curCX[x.plan[i][j]] = i;
                curCY[x.plan[i][j]] = j;
            }
    }
    debug(x.plan);
    //cout << res.size()-1 << "\n";
    //for (int i = 0;i < res.size(); ++i)
    //    cout << 1+res[i].first << " " << 1+res[i].second << "\n";
    return true;
}

int main() {
    CCCC=0;
    /*int n = 3;
    int m = 3;
    vector<vi> plan(m, vi(n, '?'));
    int id = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            plan[i][j] = char('a' + id);
            ++id;
        }
    }
    State st;
    st.plan = plan;
    st.i = m/2;
    st.j = n/2;
    dfs(st);
    debug(used.size());*/

    int n, m;
    cin >> n >> m;
    vii origin(n, vi(m, -1));
    vii target(n, vi(m, -1));
    for (int i = 0 ;i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cin >> origin[i][j];
    }
    for (int i = 0 ;i < n; ++i) {
        for (int j = 0; j < m; ++j)
            cin >> target[i][j];
    }
    vector<vi> plan(n, vi(m, 0));
    vii t2(target);
    vii o3(origin);

    int I = 0;
    for (int x = 0; x + 2 * (m>1) < n; ++x) {
        for (int y = 0; y < m; ++y) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (origin[i][j] == target[x][y]) {
                        target[x][y] = -2;
                        origin[i][j] = -1;
                        plan[i][j] = I;
                        XS[I] = x;
                        YS[I] = y;
                        curCX[I] = i;
                        curCY[I] = j;

                        ++I;
                    }
                }
            }
        }
    }

    if (m>1){
    for (int y = 0; y < m; ++y) {
        for (int x = max(n-2, 0); x < n; ++x) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (origin[i][j] == target[x][y]) {
                        target[x][y] = -2;
                        origin[i][j] = -1;
                        plan[i][j] = I;
                        XS[I] = x;
                        YS[I] = y;

                        curCX[I] = i;
                        curCY[I] = j;
                        ++I;
                    }
                }
            }
        }
    }
    }

    if (n == 1) {
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j) {
                vii o2(o3);
                int x = i;
                vector<pii> res;
                res.push_back(pii(0, x));
                while (x != j) {
                    int nx = x+(j-x)/abs(j-x);
                    swap(o2[0][x], o2[0][nx]);
                    res.push_back(pii(0, nx));
                    x = nx;
                }
                if (o2 == t2) {
                    cout << res.size()-1 << "\n";
                    for (int i = 0;i < res.size(); ++i)
                        cout << 1+res[i].first << " " << 1+res[i].second << "\n";
                    return 0;
                }
            }
        cout << "-1\n";
        return 0;
    }
    if (m == 1) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                vii o2(o3);
                int x = i;
                vector<pii> res;
                res.push_back(pii(x,0));
                while (x != j) {
                    int nx = x+(j-x)/abs(j-x);
                    swap(o2[x][0], o2[nx][0]);
                    res.push_back(pii(nx,0));
                    x = nx;
                }
                if (o2 == t2) {
                    cout << res.size()-1 << "\n";
                    for (int i = 0;i < res.size(); ++i)
                        cout << 1+res[i].first << " " << 1+res[i].second << "\n";
                    return 0;
                }
            }
        cout << "-1\n";
        return 0;
    }

    debug(plan)
    State st;
    st.plan = plan;
    st.i = curCX[plan.size() * plan[0].size() - 1];
    st.j = curCY[plan.size() * plan[0].size() - 1];
    vector<pii> res;
    if (go(st, res)) {
        cout << res.size()-1 << "\n";
        for (int i = 0;i < res.size(); ++i)
            cout << 1+res[i].first << " " << 1+res[i].second << "\n";
    } else {
        cout << "-1\n";
    }

    return 0;
}
