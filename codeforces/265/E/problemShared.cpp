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
#include <memory>
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

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class Number {
public:
    static const size_t UNDEFINED_BIT = -1;
    virtual ~Number() {}
    virtual size_t bitLength() const = 0;
    virtual size_t lastZeroBitAfter(size_t) const = 0;
    virtual size_t hash() const = 0;
    virtual void setBits(size_t bitsBegin, size_t bitsEnd, bool value) = 0;
    virtual bool getBit(size_t bit) const = 0;
    virtual bool operator<(const Number& ) const = 0;
    virtual unique_ptr<Number> clone() const = 0;
};

void out(const Number* x);

int CC, MC;

class Bit: public Number {
public:
    explicit Bit(bool v):
        val_(v) {++CC;
            assert(CC < 10000000); MC = max(MC, CC);
        }
    size_t bitLength() const override {
        return 1;
    }
    size_t lastZeroBitAfter(size_t minPosition) const override {
        size_t r = (val_ || minPosition > 0)? UNDEFINED_BIT : 0;
        return r;
    }
    size_t hash() const override {
        return val_ ? 3:2;
    }
    void setBits(size_t bitsBegin, size_t bitsEnd, bool value) override {
        assert(bitsBegin == 0 && bitsEnd == 1);
        val_ = value;
    }
    bool getBit(size_t bit) const override {
        assert(bit == 0);
        return val_;
    }
    unique_ptr<Number> clone() const override {
        ++CC;
        assert(CC < 10000000); MC = max(MC, CC);
        return make_unique<Bit>(*this);
    }
    bool operator<(const Number& o) const override {
        const Bit& b = dynamic_cast<const Bit&>(o);
        return val_ < b.val_;
    }
    ~Bit(){
        --CC;
        assert(CC < 10000000); MC = max(MC, CC);
    }
private:
    bool val_;
};

size_t b[1<<20];
size_t composeHash(size_t hash1, size_t hash2, size_t len2) {
    return hash1 * b[len2] + hash2;
}

class NumbersFactory;

class ComposeNumber: public Number {
public:
    ComposeNumber(shared_ptr<Number> a, shared_ptr<Number> b, NumbersFactory& factory):
        left_(a),
        right_(b),
        hash_(composeHash(a->hash(), b->hash(), b->bitLength())),
        length_(a->bitLength() + b->bitLength()),
        factory_(factory) {
            ++CC;
            assert(CC < 10000000); MC = max(MC, CC);
    }
    size_t bitLength() const override {
        return length_;
    }
    size_t hash() const override {
        return hash_;
    }
    size_t lastZeroBitAfter(size_t minPosition) const override {
        if (minPosition < length_/2) {
            size_t leftLastZeroBit = left_->lastZeroBitAfter(minPosition);
            if (leftLastZeroBit != UNDEFINED_BIT)
                return leftLastZeroBit;
            minPosition = length_/2;
        }
        minPosition -= length_/2;
        size_t rightLastZeroBit = right_->lastZeroBitAfter(minPosition);
        if (rightLastZeroBit == UNDEFINED_BIT)
            return UNDEFINED_BIT;
        return length_/2 + rightLastZeroBit;
    }
    void setBits(size_t bitsBegin, size_t bitsEnd, bool value) override {
        if (bitsEnd < bitsBegin)
            return;
        assert(bitsBegin <= bitsEnd);
        assert(bitsEnd <= length_);
        if (bitsBegin < length_ / 2) {
            setBits(left_, bitsBegin, min(length_/2, bitsEnd), value);
        }
        if (bitsEnd >= length_ / 2) {
            setBits(right_, max(length_/2, bitsBegin) - length_/2, bitsEnd - length_/2, value);
        }
        hash_ = composeHash(left_->hash(), right_->hash(), right_->bitLength());
    }
    bool getBit(size_t bit) const override {
        if (bit < length_/2)
            return left_->getBit(bit);
        return right_->getBit(bit - length_ / 2);
    }
    unique_ptr<Number> clone() const override {
            ++CC;
            assert(CC < 10000000); MC = max(MC, CC);
        return make_unique<ComposeNumber>(*this);
    }
    bool operator<(const Number& o) const override {
        const ComposeNumber& c = dynamic_cast<const ComposeNumber&>(o);
        /*debug(length_/2);
        out(right_.get());cerr << " ";
        debug(right_->hash());
        out(c.right_.get());cerr << " ";
        debug(c.right_->hash());*/
        if (c.right_->hash() == right_->hash())
            return (*left_) < (*c.left_);
        return (*right_) < (*c.right_);
    }
    ~ComposeNumber() {
        --CC;
        assert(CC < 10000000); MC = max(MC, CC);
    }
private:
    void setBits(shared_ptr<Number>& x, size_t bitsBegin, size_t bitsEnd, bool value);
    shared_ptr<Number> left_;
    shared_ptr<Number> right_;
    size_t hash_;
    size_t length_;
    NumbersFactory& factory_;
};

class NumbersFactory {
public:
    std::shared_ptr<Number> get(bool value, size_t len) {
        assert((len & (len - 1)) == 0);
        auto key = make_pair(value, len);
        if (data_.count(key) > 0) {
            return data_[key];
        }
        if (len == 1) {
            return data_[key] = make_shared<Bit>(value);
        }
        return data_[key] = make_shared<ComposeNumber>(
                get(value, len / 2),
                get(value, len / 2), *this);
    }
private:
    std::map<pair<bool, size_t>, std::shared_ptr<Number>> data_;
};

void ComposeNumber::setBits(shared_ptr<Number>& x, size_t bitsBegin, size_t bitsEnd, bool value) {
    assert(bitsBegin <= x->bitLength() && bitsEnd <= x->bitLength());
    if (bitsBegin >= bitsEnd) {
        return;
    }
    if (bitsBegin == 0 && x->bitLength() == bitsEnd) {
        x = factory_.get(value, x->bitLength());
    } else {
        // copy on write idiom
        x = x->clone();
        x->setBits(bitsBegin, bitsEnd, value);
    }
}

void out(const Number* x) {
    for (int i = 0; i < x->bitLength(); ++i) {
        cerr << x->getBit(i);
    }
}

shared_ptr<Number> add(const Number* a, size_t power2) {
    shared_ptr<Number> res = a->clone();
    size_t pos = res->lastZeroBitAfter(power2);
    res->setBits(power2, pos, 0);
    res->setBits(pos, pos + 1, 1);
    return res;
}

struct Cmp {
    bool operator()(const pair<shared_ptr<Number>, size_t>& a,
        const pair<shared_ptr<Number>, size_t>& b) const {
        if (*a.first < *b.first)
            return true;
        if (*b.first < *a.first)
            return false;
        return a.second < b.second;
    }
};

int main() {{
    b[0] = 1;
    for (int i = 1; i < (1<<20); ++i) {
        b[i] = b[i-1] * 5;
    }
    CC = MC = 0;
    NumbersFactory factory;
    debug(sizeof(ComposeNumber));
    debug(sizeof(Bit));
    if (0) {
        auto x = factory.get(0, 4);
        auto y = factory.get(0, 4);
        x = add(x.get(), 0);
        x = add(x.get(), 2);
        out(x.get()); cerr << "\n";
        y = add(y.get(), 0);
        y = add(y.get(), 1);
        out(y.get()); cerr << "\n";

        debug(x->hash());
        debug(y->hash());
        debug(*x < *y);
        debug(*y < *x);
        return 0;
    }
    if (0) {
        auto x = factory.get(0, 32);
        auto y = factory.get(0, 32);
        x = add(x.get(), 4);
        x = add(x.get(), 6);
        out(x.get()); cerr << "\n";
        y = add(y.get(), 1);
        y = add(y.get(), 2);
        y = add(y.get(), 3);
        y = add(y.get(), 4);
        y = add(y.get(), 5);
        out(y.get()); cerr << "\n";

        debug(*x < *y);
        debug(*y < *x);
        return 0;
    }
    if (0){
        int len = 10;
        auto x = factory.get(0, 1 << len);
        auto y = factory.get(1, 1 << len);
        debug(CC);
        vector<shared_ptr<Number>> r;
        r.push_back(x);
        for (int i = 0; i < 10000; ++i) {
            r.push_back(add(r[rand() % r.size()].get(), rand() % len));
            debug(CC);
        }
        return 0;
    }
    /*auto x = factory.get(0, 4);
    auto y = factory.get(0, 4);
    x = add(x.get(), 0);
    x = add(x.get(), 2);
    y = add(y.get(), 1);
    out(x.get()); cerr << "\n";
    out(y.get()); cerr << "\n";
    debug(*x < *y);
    debug(*y < *x);
    return 0;*/

    const int BasicLen = 1 << 17;
    //const int BasicLen = 32;

    size_t n, m, s, t;
    cin >> n >> m;
    vector<vector<pii>> al(n);
    for (int i = 0; i < m; ++i) {
        size_t a,b,x;
        cin >> a >> b >> x;
        --a;--b;
        al[a].push_back(pii(b, x));
        al[b].push_back(pii(a, x));
    }
    cin >> s >> t;
    --s;--t;

    std::set<pair<shared_ptr<Number>, size_t>, Cmp> Q;
    vector<shared_ptr<Number>> dist;
    vector<size_t> prev(n, -1);
    for (int i = 0; i < n; ++i) {
        dist.push_back(factory.get(1, BasicLen));
    }
    dist[s] = factory.get(0, BasicLen);
    Q.insert(make_pair(dist[s], s));
    while(!Q.empty()) {
        assert(Q.size() <= n);
        /*std::cerr << "{\n";
        for (auto x: Q) {
            out(x.first.get());
            cerr << ", " << x.second << "\n";
        }
        std::cerr << "}\n";*/
        size_t v = Q.begin()->second;
        Q.erase(Q.begin());
        for (size_t i = 0; i < al[v].size(); ++i) {
            size_t v2 = al[v][i].first;
            shared_ptr<Number> newDist = add(dist[v].get(), al[v][i].second);
            if (*newDist < *dist[v2]) {
                //out(newDist.get());cerr << " < ";
                //out(dist[v2].get());cerr << "\n";
                prev[v2] = v;
                Q.erase(make_pair(dist[v2], v2));
                dist[v2] = newDist;
                Q.insert(make_pair(dist[v2], v2));
            }
        }
    }

    if (dist[t]->getBit(BasicLen - 1)) {
        cout << "-1\n";
    } else {
        size_t r = 0;
        for (int i = BasicLen - 1; i >= 0; --i) {
            r = 2 * r + dist[t]->getBit(i);
            r %= 1000000007;
        }
        cout << r << "\n";
        vector<size_t> path;
        path.push_back(t);
        while(prev[path.back()] != -1) {
            path.push_back(prev[path.back()]);
        }
        reverse(all(path));
        cout << path.size() << "\n";
        for (size_t x: path) {
            cout << x + 1 << " ";
        }
        cout << "\n";
    }
    debug(MC);}
    assert(CC == 0);
    return 0;
}
