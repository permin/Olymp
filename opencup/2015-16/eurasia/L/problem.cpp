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

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;
#endif

vector<string> fieldColors = {
    "rwwgwwwrwwwgwwr",
	"wbwwwywwwywwwbw",
	"wwbwwwgwgwwwbww",
	"gwwbwwwgwwwbwwg",
	"wwwwbwwwwwbwwww",
	"wywwwwwwwwwwwyw",
	"wwgwwwgwgwwwgww",
	"rwwgwwwswwwgwwr",
	"wwgwwwgwgwwwgww",
	"wywwwwwwwwwwwyw",
	"wwwwbwwwwwbwwww",
	"gwwbwwwgwwwbwwg",
	"wwbwwwgwgwwwbww",
	"wbwwwywwwywwwbw",
	"rwwgwwwrwwwgwwr"
};

int letterCoeffByColor[256];
int wordCoeffByColor[256];
int letterPrice[33];

int doWord(vector<string>& field, int& num) {
    int res = 0;
    int coef = 1;

    int len;
    cin >> len;
    string dir;
    cin >> dir;
    int x,y;
    cin >> x >> y;
    --x;
    --y;
    int dx, dy;
    dx = dy = 0;
    if (dir == "v") {
        dy = 1;
    } else {
        dx = 1;
    }
    int p = 0;
    for (int i = 0; i < len; ++i) {
        int letter;
        cin >> letter;

        coef *= wordCoeffByColor[(int)fieldColors[y][x]];
        res += letterPrice[letter] * letterCoeffByColor[(int)fieldColors[y][x]];

        if (field[y][x] == '?') {
            --num;
            ++p;
        }
        field[y][x] = char('a' + letter - 1);

        x += dx;
        y += dy;
    }
    assert(p > 0);
    return res * coef;
}

int doMove(vector<string>& field) {
    debug(field);
    int words = 0;
    cin >> words;
    int res = 0;
    int num = 7;
    for (int i = 0; i < words; ++i) {
        res += doWord(field, num);
        debug(field);
        debug(num);
        assert(num >= 0);
    }
    if (num == 0)
        res += 15;
    return res;

}

int main() {
    std::ios_base::sync_with_stdio(false);
    letterCoeffByColor[(int)'w'] = 1;
    letterCoeffByColor[(int)'s'] = 1;
    letterCoeffByColor[(int)'g'] = 2;
    letterCoeffByColor[(int)'y'] = 3;
    letterCoeffByColor[(int)'b'] = 1;
    letterCoeffByColor[(int)'r'] = 1;

    wordCoeffByColor[(int)'w'] = 1;
    wordCoeffByColor[(int)'s'] = 1;
    wordCoeffByColor[(int)'g'] = 1;
    wordCoeffByColor[(int)'y'] = 1;
    wordCoeffByColor[(int)'b'] = 2;
    wordCoeffByColor[(int)'r'] = 3;

    letterPrice[1]=1;
letterPrice[2]=3;
letterPrice[3]=2;
letterPrice[4]=3;
letterPrice[5]=2;
letterPrice[6]=1;
letterPrice[7]=5;
letterPrice[8]=5;
letterPrice[9]=1;
letterPrice[10]=2;
letterPrice[11]=2;
letterPrice[12]=2;
letterPrice[13]=2;
letterPrice[14]=1;
letterPrice[15]=1;
letterPrice[16]=2;
letterPrice[17]=2;
letterPrice[18]=2;
letterPrice[19]=2;
letterPrice[20]=3;
letterPrice[21]=10;
letterPrice[22]=5;
letterPrice[23]=10;
letterPrice[24]=5;
letterPrice[25]=10;
letterPrice[26]=10;
letterPrice[27]=10;
letterPrice[28]=5;
letterPrice[29]=5;
letterPrice[30]=10;
letterPrice[31]=10;
letterPrice[32]=3;


    vector<string> field(fieldColors.size(), string(fieldColors[0].size(), '?'));
    int n, m;
    cin >> n >> m;
    vi score(n);
    for (int i = 0; i < m; ++i) {
        score[i % n] += doMove(field);
    }
    for (int i = 0; i < n; ++i) {
        cout << score[i] << " ";
    }
    cout << "\n";

    return 0;
}
