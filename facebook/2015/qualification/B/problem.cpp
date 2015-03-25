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
#include <thread>
#include <utility>
#include <tuple>
#include <future>
#include <condition_variable>
#include <thread>
#include <chrono>

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

class Solver {
public:
    explicit Solver(int testId = -1):
       testId_(testId){}

    string solve() {
        {
            std::unique_lock<std::mutex> lk(lock_);
            std::cerr << "Enter solve() " << testId_ << " test\n";
        }
        std::unique_lock<std::mutex> lk(lock_);
        cv_.wait(lk, [this] {return test_ == testId_;});

        std::valarray<int> goal(3);
        std::cerr << "Reading input for " << testId_ << "test.\n";
        cin >> goal[0] >> goal[1] >> goal[2];
        int n;
        cin >> n;
        vector<valarray<int>>items(n, valarray<int>(3));
        for (int i = 0; i < n; ++i) {
            cin >> items[i][0];
            cin >> items[i][1];
            cin >> items[i][2];
        }

        //std::cerr << "Read " << testId_ << "\n";

        ++test_;
        cv_.notify_all();
        std::cerr << "Start to solve " << testId_ << " test." << std::endl;
        std::cerr << std::this_thread::get_id() << "from thread." << std::endl;
        lk.unlock();

        for (int mask = 0; mask < 8*(1 << n); ++mask) {
            valarray<int> sum(3);
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i))
                    continue;
                sum += items[i];
            }

            if (sum[0] == goal[0] &&
                    sum[1] == goal[1] &&
                    sum[2] == goal[2]) {
                return "yes";
            }
        }
        return "no";
    }

private:
    int testId_;
    static std::condition_variable cv_;
    static std::mutex lock_;
    static int test_;
    int data[100];
};

void solve() {
    std::valarray<int> goal(3);
    cin >> goal[0] >> goal[1] >> goal[2];
    int n;
    cin >> n;
    vector<valarray<int>>items(n, valarray<int>(3));
    for (int i = 0; i < n; ++i) {
        cin >> items[i][0];
        cin >> items[i][1];
        cin >> items[i][2];
    }
    for (int mask = 0; mask <  (1 << n); ++mask) {
        valarray<int> sum(3);
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i))
                continue;
            sum += items[i];
        }

        if (sum[0] == goal[0] &&
                sum[1] == goal[1] &&
                sum[2] == goal[2]) {
            cout << "yes\n";
            return;
        }
    }
    cout << "no\n";
}

int Solver::test_ = 0;
std::mutex Solver::lock_;
std::condition_variable Solver::cv_;

int main() {
    std::ios_base::sync_with_stdio(false);
    freopen("input.txt", "r", stdin);
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cout << "Case #"<<t+1<<": ";
        solve();
    }
    return 0;
    std::vector<std::future<std::string>> answers;
    std::vector<Solver> solvers_(tests);
    /*const size_t maxThreads = 8;

    {
        int i = 0;
        while (i < tests) {
            std::vector<std::thread> threads;
            int k = 0;
            while(k < maxThreads && i < tests) {
                solvers_[i] = Solver(i);
                threads.push_back(std::move(std::thread(
                    std::bind(&Solver::solve, solvers_[i]))));
                ++k;
                ++i;
            }
            for (auto& t: threads)
                t.join();
        }
    }
    return 0;
    */
    for (int i = 0; i < tests; ++i) {
        solvers_[i] = Solver(i);
        answers.push_back(std::async(std::launch::async, std::bind(&Solver::solve, solvers_[i])));
    }

    //std::cerr << "--\n";

    for (int i = 0; i < tests; ++i) {
        std::cout << "Case #" << i + 1 << ": " << answers[i].get() << "\n";
    }

    return 0;
}
