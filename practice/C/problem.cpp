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

// supports find_by_order(int) and order_of_key(Key)
template<class Key, class Value>
using MapWithOrderStatistics = tree<Key, Value,
      std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
      tree_order_statistics_node_update>;

template<class Data>
struct Node;

template<class Data>
size_t getSubtreeSize(Node<Data>* r);

struct UpitData {
    UpitData():
        sum(0),yValue(0),slope(0), value(-1), actual(0){}
    explicit UpitData(size_t x):
        sum(x),yValue(0),slope(0), value(-1), actual(x){}
    size_t sum;
    size_t yValue;
    size_t slope;
    size_t value;
    size_t actual;
};

ostream& operator<<(ostream& o, const UpitData& data) {
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
    return n * (n + 1) / 2;
}

size_t sum(size_t x, size_t y) {
    return sum(y) - (x?sum(x-1):0);
}

void apply(NodePtr<UpitData> root, size_t value) {
    root->data.actual = value;
    if (value != -1) {
        root->data.slope = root->data.yValue = 0;
        root->data.value = value;
        root->data.sum = value * root->subtreeSize;
    }
}

void apply(NodePtr<UpitData> root, size_t yValue, size_t slope) {
    root->data.actual += yValue;
    root->data.actual += slope * (1 + getSubtreeSize(root->left));
    root->data.yValue += yValue;
    root->data.slope += slope;
    root->data.sum += yValue * root->subtreeSize + sum(1, root->subtreeSize) * slope;
}

template<>
void push<UpitData>(NodePtr<UpitData> root) {
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
        apply(root->right, root->data.yValue + root->data.slope * leftSize, root->data.slope);
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
void update(NodePtr<UpitData> root) {
    root->data.sum = root->data.actual;
    if (root->left) {
        root->data.sum += root->left->data.sum;
    }
    if (root->right) {
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
    int val = (rand() * rand()) % sum;
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
    enum T{Set, Linear, Insert, Sum};
    T type;
    size_t left, right, position, value;
};

ostream& operator<<(ostream& o, const Query& q) {
    if (q.type == Query::T::Set) {
        return o << "set from " << q.left << " to " << q.right << " as " << q.value;
    }
    if (q.type == Query::T::Linear) {
        return o << "add linear from " << q.left << " to " << q.right << " " << q.value;
    }
    if (q.type == Query::T::Insert) {
        return o << "insert " << q.value << " after " << q.position;
    }
    if (q.type == Query::T::Sum) {
        return o << "get sum from " << q.left << " to " << q.right;
    }
    return o;
}

size_t apply(Query q, NodePtr<UpitData>& root) {
    NodePtr<UpitData> left;
    NodePtr<UpitData> right;
    NodePtr<UpitData> middle;
    middle = left = right = 0;
    size_t res = -1;
    if (q.type == Query::T::Set || q.type == Query::T::Sum || q.type == Query::T::Linear) {
        split(root, q.left, &left, &middle);
        split(middle, q.right - q.left + 1, &middle, &right);
        if (q.type == Query::T::Linear)
            apply(middle, 0,q.value);
        if (q.type == Query::T::Set)
            apply(middle, q.value);
        if (q.type == Query::T::Sum)
            res = middle->data.sum;
    } else if (q.type == Query::T::Insert) {
        split(root, q.position, &left, &right);
        middle = new Node<UpitData>(UpitData(q.value));
    }
    merge(left, middle, &left);
    merge(left, right, &root);
    return res;
}

size_t apply(Query q, vector<size_t>& tree) {
    size_t res = -1;
    if (q.type == Query::T::Sum) {
        res = 0;
    }
    if (q.type == Query::T::Set || q.type == Query::T::Sum || q.type == Query::T::Linear) {
        size_t add = q.value;
        for (size_t i = q.left; i <= q.right; ++i) {
            if (q.type == Query::T::Sum) {
                res += tree[i];
            }
            if (q.type == Query::T::Set) {
                tree[i] = q.value;
            }
            if (q.type == Query::T::Linear) {
                tree[i] += add;
                add += q.value;
            }
        }
    }
    if (q.type == Query::T::Insert) {
        tree.insert(tree.begin() + q.position, q.value);
    }
    return res;
}

vector<Query> genQueries(int len = 50, int queries = 10000) {
    vector<Query> res;
    for (int i = 0; i < len; ++i) {
        Query q;
        q.type = Query::T::Insert;
        q.position = i;
        q.value = rand() % 10;
        res.push_back(q);
    }
    for (int i = 0; i < queries; ++i) {
        Query q;
        int j = rand() % 4;
        if (j == 0) {
            q.type = Query::T::Set;
            q.left = rand() % len;
            q.right = rand() % len;
            if (q.left > q.right)
                swap(q.left, q.right);
            q.value = rand() % 100;
        }
        if (j == 1) {
            q.type = Query::T::Linear;
            q.left = rand() % len;
            q.right = rand() % len;
            if (q.left > q.right)
                swap(q.left, q.right);
            q.value = rand() % 100;
        }
        if (j == 2) {
            q.type = Query::T::Insert;
            q.position = rand() % len;
            ++len;
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

int main() {
    srand(time(0));
    /*NodePtr<int> root = 0;
    for (int i = 1; i <= 50; ++i) {
        debug(i);
        merge(root, new Node<int>(i), &root);
        //debug(*root);
        //debug(getSubtreeSize(root));
    }
    size_t total = getSubtreeSize(root);
    for (int k = 0; k <= total; ++k) {
        NodePtr<int> l,r;
        split(root, k, &l, &r);
        assert(getSubtreeSize(l) == k);
        assert(getSubtreeSize(r) == total - k);
        merge(l, r, &root);
        assert(getSubtreeSize(root) == total);
    }*/
    auto qs = genQueries(100*1000,900*1000);
    /*qs.clear();
    qs.push_back({Query::T::Insert,0,0,0,0});
    qs.push_back({Query::T::Insert,0,0,0,0});
    qs.push_back({Query::T::Insert,0,0,0,0});
    qs.push_back({Query::T::Insert,0,0,0,0});
    qs.push_back({Query::T::Insert,0,0,0,0});
    qs.push_back({Query::T::Insert,0,0,0,0});
    qs.push_back({Query::T::Linear,0,5,0,10});
    qs.push_back({Query::T::Sum,1,3,0,10});*/
    debug(qs.size());
    vector<size_t> correct, my;
    NodePtr<UpitData> root = 0;
    vector<size_t> tree;
    for (int i = 0; i < qs.size(); ++i) {
        //debug(i);
        auto q = qs[i];
        //debug(q);
        my.push_back(apply(q, root));
        //correct.push_back(apply(q, tree));
        //debug(root->subtreeSize);
        //debug(root->data);
        //out(root);
        //debug(tree);
        /*if (correct != my) {
            debug(my);
            debug(correct);
            assert(correct == my);
        }*/
    }
    debug(root->subtreeSize);
    debug(root->data);
    return 0;
}
