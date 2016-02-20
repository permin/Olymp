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

#if GCC_VERSION > 40900
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#endif
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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

const int MaxN = 10*1000 * 1000 + 1030;

int suffixLink[MaxN];
int terminalLink[MaxN];
int ids[MaxN];
int transitions[MaxN][2];

int pr[800];

int newNode() {
    static int i = 1;
    /*suffixLink[i] = 0;
    terminalLink[i]=-1;
    transitions[i][0] = transitions[i][1] = -1;
    ids[i] = -1;*/
    return i++;
}

void addString(int n, const string& s, int id) {
    for (char ch: s) {
        if (transitions[n][ch] == -1) {
            transitions[n][ch] = newNode();
        }
        n = transitions[n][ch];
    }
    if (ids[n] == -1) {
        ids[n] = id;
    } else {
        pr[id] = ids[n];
        ids[n] = id;
    }
}

/*inline int getTransition(int n, char ch) {
    if (nodes[n].transitions[ch] != -1) {
        return nodes[n].transitions[ch];
    }
    if (!n) return n;
    return nodes[n].transitions[ch] = getTransition(nodes[n].suffixLink, ch);
}*/

int Q[MaxN];

void calcSuffixLinks() {
    throw 2;
    int head, tail;
    head = tail = 0;
    Q[tail++] = 0;
    while(head != tail) {
        int n = Q[head++];
        for (char ch = 0; ch < 2; ++ch) {
            if (transitions[n][ch] == -1)
                continue;
            int n2 = transitions[n][ch];
            int suf = n;
            do {
                suf = suffixLink[suf];
                if (transitions[suf][ch] != -1 && transitions[suf][ch] != n2) {
                    suffixLink[n2] = transitions[suf][ch];
                    debug(n2);
                    break;
                }
            } while(suf);
            //Q.push(n2);
            Q[tail++] = n2;
        }
        if (!n) {
            continue;
        }
        if (ids[suffixLink[n]]!= -1) {
            terminalLink[n] = suffixLink[n];
        } else {
            terminalLink[n] = terminalLink[suffixLink[n]];
        }
        {
            for (char ch = 0; ch < 2; ++ch) {
                int m = n;
                while (true) {
                    if (transitions[m][ch] >= 0) {
                        transitions[n][ch] = transitions[m][ch];
                        break;
                    }
                    if (m == 0) {transitions[n][ch] = 0;break;}
                    m = suffixLink[m];
                }
            }
        }
    }
}

bool dfs(int v, vector<bool>& used, const vii& al, vi& R) {
    if (used[v])
        return 0;
    used[v] = 1;
    for (int v2: al[v]) {
        if (R[v2] == -1 || dfs(R[v2], used, al, R)) {
            R[v2] = v;
            return 1;
        }
    }
    return 0;
}
char buf[MaxN];

int rel[750][750];

int main() {

    memset(suffixLink, 0, sizeof(suffixLink));
    memset(terminalLink, -1, sizeof(terminalLink));
    memset(ids, -1, sizeof(ids));
    memset(transitions, -1, sizeof(transitions));
    /*suffixLink[i] = 0;
    terminalLink[i]=-1;
    transitions[i][0] = transitions[i][1] = -1;
    ids[i] = -1;*/

    suffixLink[0] = 0;
    terminalLink[0]=-1;
    transitions[0][0] = transitions[0][1] = -1;
    ids[0] = -1;

    std::ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
        pr[i] = -1;
    vector<string> words(n);
    for (auto& s: words) {
        //scanf("%s", buf);
        //s = string(buf);
        cin >> s;
        for (char& ch: s) {
            ch -= 'a';
        }
    }
    for (int i = 0; i < n; ++i) {
        addString(0, words[i], i);
    }
    calcSuffixLinks();
    cerr << "aho is build\n";

    //vii rel(n, vi(n, 0));
    for (int i = 0; i < n; ++i) {
        int n = 0;
        for (char ch: words[i]) {
            debug(ch);
            n = transitions[n][ch];
            debug(n);
            {
                int m = n;
                while(m >= 0) {
                    int id = ids[m];
                    while (id >= 0) {
                        rel[i][id] = 1;
                        id = pr[id];
                    }
                    m = terminalLink[m];
                    debug(m);
                }
            }
        }
    }
    cerr << "rel is found\n";
    vi u;
    for (int i = 0; i < n; ++i) {
        bool ok = true;
        for (int j: u) {
            if (rel[i][j] && rel[j][i])
                ok = 0;
        }
        if (ok)
            u.push_back(i);
    }

    vii al(n);
    for (int k: u) {
        for (int j = 0; j < n; ++j) {
            if (rel[k][j] && binary_search(all(u), j) && k != j) {
                al[k].push_back(j);
            }
        }
    }

    debug(u);
    debug(rel);
    debug(al);

    vi R(n, -1);
    int matched = 0;
    vector<int> order;
    for (int i: u) {
        for (int j: al[i]) {
            if (R[j] == -1) {
                R[j] = i;
                goto gg;
                break;
            }
        }
        order.push_back(i);
gg:;
    }

    random_shuffle(all(order));
    for (int i: order) {
        vector<bool> used(n);
        matched += dfs(i, used, al, R);
    }
    debug(matched);

    vi sources;
    for (int i: u) {
        if (count(all(R), i) > 0)
            continue;
        sources.push_back(i);
    }
    debug(sources);
    debug(R);

    vii chains(sources.size());
    for (int i = 0; i < (int)sources.size(); ++i) {
        int s = sources[i];
        chains[i].push_back(s);
        while(R[s] >= 0) {
            s = R[s];
            chains[i].push_back(s);
        }
    }
    vi ptrs(chains.size(), 0);
    bool ch = 0;
    do {
        ch = 0;
        for (int i = 0; i < ptrs.size(); ++i) {
            for (int j = 0; j < ptrs.size(); ++j) {
                if (i != j && rel[chains[j][ptrs[j]]][chains[i][ptrs[i]]]) {
                    ch = 1;
                    ++ptrs[i];
                    goto g;
                }
            }
        }
g:;
    } while (ch);

    cout << chains.size() << "\n";
    for (size_t i = 0; i < ptrs.size(); ++i) {
        cout << chains[i][ptrs[i]] + 1 << " ";
    }
    cout << "\n";

    return 0;
}
