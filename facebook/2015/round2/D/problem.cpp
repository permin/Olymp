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

const int MOD = 1e9;

size_t add(size_t x, size_t y) {
    x += y;
    return x % MOD;
}

size_t mul(size_t x, size_t y) {
    size_t res = 1LL * x * y;
    return res % MOD;
}

size_t sub(size_t x, size_t y) {
    return add(x, (MOD - (y%MOD)));
}


template<class Data>
struct Node;

template<class Data>
size_t getSubtreeSize(Node<Data>* r);

struct SocksData {
    SocksData():
        sum(0),yValue(0),slope(0), oddsInOdd(0), oddsInEven(0), value(-1), actual(0), index(-1){}
    explicit SocksData(size_t x, size_t index):
        sum(x),yValue(0),slope(0), oddsInOdd(0), oddsInEven(0), value(-1), actual(x), index(index){
            if (index & 1) {
                oddsInOdd += (x & 1);
            } else {
                oddsInEven += (x & 1);
            }
        }

    size_t sum;
    size_t yValue;
    size_t slope;
    size_t oddsInOdd, oddsInEven;
    size_t value;
    size_t actual;
    size_t index;
};

ostream& operator<<(ostream& o, const SocksData& data) {
    o << "{sum: " << data.sum << ", " <<
        "set: " << data.value << ", " <<
        "actual: " << data.actual << ", " <<
        "linear: " << data.slope << " * x";
    if (data.yValue > 0) {
        o << " + " << data.yValue;
    }
    return o << "}";
}

template<class Data>
struct Node {
    explicit Node(Data d = Data()):
        left(0),
        right(0),
        data(d),
        subtreeSize(1) {}
    Node* left;
    Node* right;
    Data data;
    size_t subtreeSize;
};

template<class Data>
using NodePtr = Node<Data>*;

template<class Data>
void push(NodePtr<Data> ) {
}

size_t sum(size_t n) {
    return (n * (n + 1) / 2) % MOD;
}

size_t sum(size_t x, size_t y) {
    return sub(sum(y) , (x?sum(x-1):0));
}

size_t evenPositionsInSubtree(NodePtr<SocksData> root);

size_t oddPositionsInSubtree(NodePtr<SocksData> root) {
    if (root->data.index & 1) {
        return 1 + (getSubtreeSize(root->left) / 2) + (getSubtreeSize(root->right) / 2);
    }
    return root->subtreeSize - evenPositionsInSubtree(root);
}

size_t evenPositionsInSubtree(NodePtr<SocksData> root) {
    if (root->data.index & 1) {
        return root->subtreeSize - oddPositionsInSubtree(root);
    }
    return 1 + (getSubtreeSize(root->left) / 2) + (getSubtreeSize(root->right) / 2);
}

void apply(NodePtr<SocksData> root, size_t value) {
    root->data.actual = value;
    if (value != -1) {
        root->data.slope = root->data.yValue = 0;

        root->data.value = value;
        root->data.sum = mul(value, root->subtreeSize);

        if (value & 1) {
            root->data.oddsInOdd = oddPositionsInSubtree(root);
            root->data.oddsInEven = evenPositionsInSubtree(root);
        } else {
            root->data.oddsInOdd = root->data.oddsInEven = 0;
        }
    }
}

void apply(NodePtr<SocksData> root, size_t yValue, size_t slope) {
    root->data.actual = add(root->data.actual, yValue);
    root->data.actual = add(root->data.actual,
            mul(slope, (1 + getSubtreeSize(root->left))));

    root->data.yValue = add(root->data.yValue, yValue);
    root->data.slope = add(slope, root->data.slope);

    root->data.sum = add(root->data.sum,
        add(mul(yValue, root->subtreeSize),
            mul(sum(0, root->subtreeSize-1), slope)));

    size_t e1 = root->data.oddsInEven;
    size_t e0 = evenPositionsInSubtree(root) - e1;

    size_t o1 = root->data.oddsInOdd;
    size_t o0 = oddPositionsInSubtree(root) - o1;

    size_t de = yValue & 1;
    size_t dod = ((yValue & 1) + (slope & 1)) & 1;

    root->data.oddsInEven = de == 0 ? e1 : e0;
    root->data.oddsInOdd = (dod == 0) ? o1 : o0;
}

template<>
void push<SocksData>(NodePtr<SocksData> root) {
    if (root->data.value != -1) {
        if (root->left)
            apply(root->left, root->data.value);
        if (root->right)
            apply(root->right, root->data.value);
    }
    if (root->left) {
        apply(root->left, root->data.yValue, root->data.slope);
    }
    if (root->right) {
        size_t leftSize = getSubtreeSize(root->left) + 1;
        apply(root->right, add(root->data.yValue, mul(root->data.slope ,leftSize)), root->data.slope);
    }
    root->data.slope = root->data.yValue = 0;
    root->data.value = -1;
}

template<class Data>
void updateSubtreeSizes(NodePtr<Data> root) {
    root->subtreeSize = 1 + getSubtreeSize(root->left) + getSubtreeSize(root->right);
}

template<class Data>
void update(NodePtr<Data> ) {
}

template<>
void update(NodePtr<SocksData> root) {
    root->data.sum = root->data.actual;
    if (root->data.index & 1) {
        root->data.oddsInOdd = root->data.actual & 1;
    } else {
        root->data.oddsInEven = root->data.actual & 1;
    }
    if (root->left) {
        root->data.oddsInOdd += root->left->data.oddsInOdd;
        root->data.oddsInEven += root->left->data.oddsInEven;
        root->data.sum += root->left->data.sum;
    }
    if (root->right) {
        root->data.oddsInOdd += root->right->data.oddsInOdd;
        root->data.oddsInEven += root->right->data.oddsInEven;
        root->data.sum += root->right->data.sum;
    }
}

template<class Data>
ostream& operator<<(ostream& o, const Node<Data>& x) {
    return o << "{" << &x << ", left: " << x.left << ", right: " << x.right <<
        ", subtreeSize: " << x.subtreeSize << ", data: " << x.data << "}";
}

template<class Data>
size_t getSubtreeSize(Node<Data>* r) {
    return !r ? 0 : r->subtreeSize;
}

template<class Data>
void split(NodePtr<Data> root, size_t leftTreeSize, NodePtr<Data>* left, NodePtr<Data>* right) {
    if (!root) {
        *left = *right = 0;
        return;
    }
    push(root);
    size_t inLeft = getSubtreeSize(root->left);
    if (inLeft >= leftTreeSize) {
        split(root->left, leftTreeSize, left, &(root->left));
        *right = root;
    } else {
        split(root->right, leftTreeSize - 1 - inLeft,
                &(root->right), right);
        *left = root;
    }
    updateSubtreeSizes(root);
    update(root);
}

template<class Data>
void merge(NodePtr<Data> left, NodePtr<Data> right, NodePtr<Data>* res) {
    if (left == 0) {
        push(right);
        *res = right;
        updateSubtreeSizes(*res);
        update(*res);
        return;
    }
    if (right == 0) {
        push(left);
        *res = left;
        updateSubtreeSizes(*res);
        update(*res);
        return;
    }

    push(left);
    push(right);

    size_t sum =
        getSubtreeSize(left) + getSubtreeSize(right);
    assert(sum);
    size_t val = (rand()) % sum;
    if (val < getSubtreeSize(left)) {
        merge(left->right, right, &(left->right));
        *res = left;
    } else {
        merge(left, right->left, &(right->left));
        *res = right;
    }
    updateSubtreeSizes(*res);
    update(*res);
}

struct Query {
    enum T{Set, Linear, Odd, Sum};
    T type;
    size_t left, right, yValue, slope;
};

ostream& operator<<(ostream& o, const Query& q) {
    if (q.type == Query::T::Set) {
        return o << "set from " << q.left << " to " << q.right << " as " << q.yValue;
    }
    if (q.type == Query::T::Linear) {
        return o << "add linear from " << q.left << " to " << q.right << " " << q.yValue<<
            " + i * " << q.slope;
    }
    if (q.type == Query::T::Odd) {
        return o << "count odds from " << q.left << " to " << q.right;
    }
    if (q.type == Query::T::Sum) {
        return o << "get sum from " << q.left << " to " << q.right;
    }
    return o;
}

size_t apply(Query q, NodePtr<SocksData>& root) {
    NodePtr<SocksData> left;
    NodePtr<SocksData> right;
    NodePtr<SocksData> middle;
    middle = left = right = 0;
    size_t res = -1;
    split(root, q.left, &left, &middle);
    split(middle, q.right - q.left + 1, &middle, &right);
    size_t len = q.right - q.left + 1;
    if (q.type == Query::T::Linear) {
        apply(middle, q.yValue, q.slope);
        res = add(mul(len, q.yValue), mul(q.slope, sum(0, len-1)));
    }
    if (q.type == Query::T::Set) {
        apply(middle, q.yValue);
        res = add(middle->data.sum, mul(len, q.yValue));
    }
    if (q.type == Query::T::Sum)
        res = middle->data.sum;
    if (q.type == Query::T::Odd)
        res = middle->data.oddsInEven + middle->data.oddsInOdd;
    merge(left, middle, &left);
    merge(left, right, &root);
    return res;
}

size_t apply(Query q, vector<size_t>& tree) {
    size_t res = 0;
        size_t add = q.yValue;
        for (size_t i = q.left; i <= q.right; ++i) {
            if (q.type == Query::T::Sum) {
                res += tree[i];
            }
            if (q.type == Query::T::Set) {
                res += tree[i];
                tree[i] = q.yValue;
                res += tree[i];
            }
            if (q.type == Query::T::Linear) {
                res += add;
                tree[i] += add;
                add += q.slope;
            }
            if (q.type == Query::T::Odd) {
                res += (tree[i] & 1);
            }
        }
    return res;
}

vector<Query> genQueries(int len = 50, int queries = 10000) {
    vector<Query> res;
    for (int i = 0; i < queries; ++i) {
        Query q;
        int j = rand() % 4;
        if (j == 0) {
            q.type = Query::T::Set;
            q.left = rand() % len;
            q.right = rand() % len;
            if (q.left > q.right)
                swap(q.left, q.right);
            q.yValue = rand() % 10;
        }
        if (j == 1) {
            q.type = Query::T::Linear;
            q.left = rand() % len;
            q.right = rand() % len;
            if (q.left > q.right)
                swap(q.left, q.right);
            q.yValue = rand() % 10;
            q.slope = rand() % 10;
        }
        if (j == 2) {
            q.type = Query::T::Odd;
            q.left = rand() % len;
            q.right = rand() % len;
            if (q.left > q.right)
                swap(q.left, q.right);
        }
        if (j == 3) {
            q.type = Query::T::Sum;
            q.left = rand() % len;
            q.right = rand() % len;
            if (q.left > q.right)
                swap(q.left, q.right);
        }
        res.push_back(q);
    }
    return res;
}

template<class Data>
void out(NodePtr<Data> root, std::string s = "") {
    if (!root) {
        return;
    }
    out(root->left, s + " L");
    cerr << s << " ";
    cerr << *root << "\n";
    out(root->right, s + " R");
}

void solve() {
    int n, q;
    cin >> n >> q;
    vector<size_t> s,o,a,b,c,d;
    s.resize(2);
    o.resize(2);
    a.resize(2);
    b.resize(2);
    c.resize(2);
    d.resize(2);
    {
        size_t x, y, z;
        cin >> s[0] >> s[1] >> x >> y >> z;
        for (int i = 2; i < q; ++i) {
            s.push_back((x*s[i-2] + y*s[i-1] + z) % MOD);
        }
    }
    {
        size_t x, y, z;
        cin >> o[0] >> o[1] >> x >> y >> z;
        for (int i = 2; i < q; ++i) {
            o.push_back(((x*o[i-2] + y*o[i-1] + z) % 4) + 1);
        }
    }
    {
        size_t x, y, z;
        cin >> a[0] >> a[1] >> x >> y >> z;
        for (int i = 2; i < q; ++i) {
            a.push_back((x*a[i-2] + y*a[i-1] + z) % n);
        }
    }
    {
        size_t x, y, z;
        cin >> b[0] >> b[1] >> x >> y >> z;
        for (int i = 2; i < q; ++i) {
            b.push_back((x*b[i-2] + y*b[i-1] + z) % n);
        }
    }
    {
        size_t x, y, z;
        cin >> c[0] >> c[1] >> x >> y >> z;
        for (int i = 2; i < q; ++i) {
            c.push_back((x*c[i-2] + y*c[i-1] + z) % MOD);
        }
    }
    {
        size_t x, y, z;
        cin >> d[0] >> d[1] >> x >> y >> z;
        for (int i = 2; i < q; ++i) {
            d.push_back((x*d[i-2] + y*d[i-1] + z) % MOD);
        }
    }
    std::vector<Query> qs;

    for (int i = 0; i < q; ++i) {
        if (o[i] == 1) {
            if (a[i] <= b[i]) {
                {
                    Query qq;
                    qq.type = Query::T::Linear;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            } else {

                {
                    Query qq;
                    qq.type = Query::T::Linear;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = n - 1;

                    qs.push_back(qq);
                }
                {
                    Query qq;
                    qq.type = Query::T::Linear;
                    qq.slope = d[i];
                    qq.yValue = add(c[i], add(c[i] , mul(sum(0, n - 1 - a[i] + 1), c[i])));
                    qq.left = 0;
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            }
        }
        if (o[i] == 2) {
            if (a[i] <= b[i]) {
                {
                    Query qq;
                    qq.type = Query::T::Set;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            } else {

                {
                    Query qq;
                    qq.type = Query::T::Set;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = n - 1;

                    qs.push_back(qq);
                }
                {
                    Query qq;
                    qq.type = Query::T::Set;
                    qq.slope = d[i];
                    qq.yValue = add(c[i], add(c[i] , mul(sum(0, n - 1 - a[i] + 1), c[i])));
                    qq.left = 0;
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            }
               /* {
                    Query qq;
                    qq.type = Query::T::Set;
                    qq.slope = d[i];
                    qq.yValue = add(c[i], add(c[i] + mul(sum(0, n - 1 - a[i] + 1), slope)));
                    qq.left = 0;
                    qq.right = b[i];

                    qs.push_back(qq);
                }*/
        }
        if (o[i] == 3) {
            if (a[i] <= b[i]) {
                {
                    Query qq;
                    qq.type = Query::T::Sum;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            } else {

                {
                    Query qq;
                    qq.type = Query::T::Sum;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = n - 1;

                    qs.push_back(qq);
                }
                {
                    Query qq;
                    qq.type = Query::T::Sum;
                    qq.slope = d[i];
                    qq.yValue = add(c[i], add(c[i] , mul(sum(0, n - 1 - a[i] + 1), c[i])));
                    qq.left = 0;
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            }
        }
        if (o[i] == 4) {

            if (a[i] <= b[i]) {
                {
                    Query qq;
                    qq.type = Query::T::Odd;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            } else {

                {
                    Query qq;
                    qq.type = Query::T::Odd;
                    qq.slope = d[i];
                    qq.yValue = c[i];
                    qq.left = a[i];
                    qq.right = n - 1;

                    qs.push_back(qq);
                }
                {
                    Query qq;
                    qq.type = Query::T::Odd;
                    qq.slope = d[i];
                    qq.yValue = add(c[i], add(c[i] , mul(sum(0, n - 1 - a[i] + 1), c[i])));
                    qq.left = 0;
                    qq.right = b[i];

                    qs.push_back(qq);
                }
            }
        }
    }

    bool de = 1;

    vector<size_t> tree;
    NodePtr<SocksData> root = 0;
    for (int i = 0; i < n; ++i) {
        merge(root, new Node<SocksData>(SocksData(s[i],i)), &root);
        if (de) {
            tree.push_back(s[i]);
        }
    }
    size_t res = 0;
    size_t res2 = 0;
    for (auto q: qs) {
        res = add(res, apply(q, root));
        if (de) {
            res2 = add(res2, apply(q, tree));
        }
        debug(res);
        debug(res2);
    }
    cout << res;
}

int main() {
    std::ios_base::sync_with_stdio(false);

    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<<t+1<<": ";
        solve();
    }

    return 0;
}
