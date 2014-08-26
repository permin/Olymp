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
#include <tuple>
#include <type_traits>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/variant.hpp>

#include <boost/assign/std/set.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/assign/list_inserter.hpp>

#include <boost/fusion/include/count.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>

using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

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

struct K {
    std::string colId;
    std::string recId;
    std::string data;
    K(const std::string& colId,
            const std::string& recId,
            const std::string& data):
        colId(colId), recId(recId), data(data) {}
};

using namespace boost::multi_index;

template<size_t I, class Tuple>
struct Getter{
    typedef typename std::tuple_element<I, Tuple>::type result_type;
    const typename std::tuple_element<I, Tuple>::type& operator()(const Tuple& tuple) const {
        return std::get<I>(tuple);
    }
};

template <class Map>
using KeysIterator =
     boost::transform_iterator<Getter<0, typename Map::value_type>, typename Map::const_iterator>;

void f(boost::variant<std::string, int> x) {
    std::cerr << x << "\n";
}

template<class T>
class IsSameClass: public boost::static_visitor<bool> {
public:
    template<class X>
    bool operator()(X) const {
        return std::is_same<T, X>::value;
    }
};

/*

template<class T>
class isIterable {
static void f(...);
template<class U>
static decltype(std::declval<U>().begin()) f(const U&);
public:
    typedef decltype(f(std::declval<T>())) iterator;
    static constexpr bool value = !std::is_same<void, iterator>::value;
};


template<class It>
struct SubIteratorsTuple {
private:
    static std::tuple<It> f(...);
    template<class U>
    static decltype(std::tuple_cat(std::tuple<It>(), SubIteratorsTuple<std::iterator_traits<U>::value_type::iterator>>::type()))  f(const U&);
public:
    typedef decltype(f(std::declval<T>()))  type;
};
template<>
struct SubIteratorsTuple<void> {
    //typedef void subIter;
    typedef std::tuple<> type;
};*/

class TT {
public:
    explicit TT():
        i(0) {}

    void inc() {
        std::cerr << "inc()\n";
        ++i;
    }
    void dec() {
        std::cerr << "dec()\n";
        --i;
    }
private:
    int i;
};

void intrusive_ptr_add_ref(TT* x) {
    x->inc();
}
void intrusive_ptr_release(TT* x) {
    x->dec();
}

template<class T>
class It_ {
public:
    It_(T* y): x(y){}
    template<class U = T>
    typename std::enable_if<!std::is_const<U>::value, U>::type& operator*() {
        return *x;
    }
    typename std::add_const<T>::type& operator*() const {
        return *x;
    }
private:
    T* x;
};

int main() {
    {
      std::string str = "abcd";
        const std::string STR = "ABCD";
        typedef It_<char> It;
        typedef It_<const char> constIt;
        It i(&str[0]);
        constIt ci(&STR[0]);
        constIt ci2(&str[0]);

        std::cerr << (*i) << "\n";
        std::cerr << (*ci) << "\n";


    }
    {
        TT x;
        boost::intrusive_ptr<TT> ptr(&x);
        boost::intrusive_ptr<TT> ptr2(ptr);

        return 0;
    }
    /*{
        typedef std::vector<std::vector<std::set<int>>> XXX;
        //typedef std::set<int> XXX;
        std::cerr << std::tuple_size<SubIteratorsTuple<XXX::iterator>::type>::value << "\n";
        return 0;
    }
    {
        boost::variant<int, std::string> x;
        x = "string";
        std::cerr << boost::bind(boost::apply_visitor, IsSameClass<std::string>(), _1)(x);
        return 0;
    }*/
    f("test");
    {
        using boost::assign::operator+=;
        std::set<int> a;
        a.insert(1);
        a.insert(2);
        a.insert(3);

        boost::iterator_range<std::set<int>::const_iterator> range(a.cbegin(), a.cend());
        std::set<decltype(range)::value_type> b;
        boost::assign::insert(b).range(range);
        std::cerr << b.size() << "\n";
    }
    {
        typedef boost::variant<std::string, int, double> V;
        V x = "hello";
        std::cerr << boost::apply_visitor(IsSameClass<int>(), x) << '\n';
        std::cerr << boost::apply_visitor(IsSameClass<std::string>(), x) << '\n';

    }
    {
        multi_index_container<
          int,
          indexed_by<
            ordered_unique<
              identity<int>
            >
          >
        > cont;
        cont.insert(1);
        cont.insert(1);
        cont.insert(2);
        std::cerr << cont.count(1) << "\n";
        std::cerr << cont.count(2) << "\n";
        std::cerr << cont.count(3) << "\n";
        for (auto x: cont) {
            std::cerr << x << " ";
        }
        std::cerr << "\n";
    }
    std::cerr << "SECOND\n";
    {
        typedef multi_index_container<
            K,
            indexed_by<
                hashed_unique<
                    composite_key<
                        K,
                        member<K, std::string, &K::colId>,
                        member<K, std::string, &K::recId>
                    >
                 >,
                hashed_non_unique<
                    member<K, std::string, &K::colId>
                >
            >
       > Diff;
        Diff cont;
        cont.insert(K("col_1", "rec_1", "diff_1_1"));
        cont.insert(K("col_1", "rec_2", "diff_1_2"));
        cont.insert(K("col_2", "rec_1", "diff_2_1"));
        for (auto x: cont) {
            std::cerr << x.data << " ";
        }
        std::cerr << "\n";
        for (auto x: cont.get<1>()) {
            std::cerr << x.data << " ";
        }
        std::cerr << "\n";
        {
            std::pair<Diff::iterator, Diff::iterator> p =
                cont.get<0>().equal_range(boost::make_tuple("col_1", "rec_1"));
            while(p.first!=p.second) {
                std::cout<<p.first->data <<std::endl;
                ++p.first;
            }
        }
        {
            std::cerr << "find:\n";
            auto it = cont.get<1>().find("col_1");
            std::cerr << it->data << "\n";
            ++it;
            std::cerr << it->data << "\n";
            ++it;
            std::cerr << it->data << "\n";
        }
        if (0) {
            std::cerr << "find:\n";
            auto it = cont.get<1>().find("col_1");
            std::cerr << it->data << "\n";
            ++it;
            std::cerr << it->data << "\n";
            ++it;
            std::cerr << it->data << "\n";
        }
        {
            std::cerr << "equal_range:\n";
            auto p = cont.get<1>().equal_range("col_1");
            while (p.first != p.second) {
                std::cout<<p.first->data << ", ";
                ++p.first;
            }
            std::cerr << "\n";
        }
        {
            std::cerr << "equal_range:\n";
            auto p = cont.get<0>().equal_range(boost::make_tuple("col_1","rec_1"));
            while (p.first != p.second) {
                std::cout<<p.first->data << ", ";
                ++p.first;
            }
            std::cerr << "\n";
        }
        /*{
            std::pair<Diff::iterator, Diff::iterator> p =
                cont.get<1>().equal_range(boost::make_tuple("col_1"));
            while(p.first!=p.second) {
                std::cout<<p.first->data <<std::endl;
                ++p.first;
            }
        }*/
    }
    {

        typedef std::unordered_map<std::string, int> M;
        M m;
        m["one"] = 1;
        m["two"] = 2;
        typedef KeysIterator<M> ti;
        ti b = ti(m.begin());
        ti e = ti(m.end());
        while (b != e) {
            std::cerr << *b << ", ";
            ++b;
        }
        std::cerr << "\n";
    }

    return 0;
}

