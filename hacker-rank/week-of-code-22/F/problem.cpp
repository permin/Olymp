#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>

#if GCC_VERSION > 40900
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
#endif
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": " << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template <class T>
class IsIterable__ {
  static void f(...);
  template <class U>
  static typename U::const_iterator f(const U &);

 public:
  const static bool value =
      !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S>
ostream &operator<<(ostream &o, const pair<F, S> &p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C>
void O__(ostream &o, const C &c) {
  bool f = 1;
  for (const auto &x : c) {
    if (!f) {
      o << ", ";
    }
    if (IsIterable__<decltype(x)>::value) {
      o << "\n";
    }
    f = 0;
    o << x;
  }
}

template <class T>
ostream &operator<<(ostream &o, const vector<T> &v) {
  o << "[";
  O__(o, v);
  o << "]";
  return o;
}

template <class T, class V>
ostream &operator<<(ostream &o, const map<T, V> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

template <class T>
ostream &operator<<(ostream &o, const set<T> &v) {
  o << "{";
  O__(o, v);
  o << "}";
  return o;
}

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
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

int add(int x, int y, int mod) { return (x + y) % mod; }
int mul(int x, int y, int mod) { return int((1LL * x * y) % mod); }

template <int kBase, int kMod>
class HashableString {
 public:
  HashableString() : powers_(1, 1), pref_hashes_(1, 0) {}

  void append(int ch) {
    symbols_.push_back(ch);
    pref_hashes_.push_back(
        add(pref_hashes_.back(), mul(ch, powers_.back(), kMod), kMod));
    powers_.push_back(mul(powers_.back(), kBase, kMod));
  }

  void pop_back() {
    symbols_.pop_back();
    pref_hashes_.pop_back();
    powers_.pop_back();
  }

  int size() const { return (int)symbols_.size(); }

  int operator[](int i) const { return symbols_[i]; }

  int hash(int begin, int end) const {
    int h = pref_hashes_[end];
    h = add(h, kMod - pref_hashes_[begin], kMod);
    return mul(h, powers_[(int)powers_.size() - 1 - begin], kMod);
  }

 private:
  vi powers_;
  vi symbols_;
  vi pref_hashes_;
  // a_0 + a_1 * b + a_2 * b^2 + ...
};

vii occurences;

struct Request {
  enum Action { Add, Remove };
  Action action;
  int symbol = -1;
};

const int kAlphabet = 500;

struct TrieNode {
  std::map<int, TrieNode> tranistions;
  vector<int> requests_ids;
  TrieNode *parent = nullptr;
};

vector<int> ans;
vector<int> prefix_function;
const int kBase = 1000 * 1000 + 3;
const int kMod7 = 1000 * 1000 * 1000 + 7;
HashableString<kBase, kMod7> string1;
HashableString<kBase, kMod7 + 2> string2;

void dfs(TrieNode *node) {
  for (int r : node->requests_ids) {
    ans[r] = prefix_function.back();
  }
  for (const auto &char_node : node->tranistions) {
    const int symbol = char_node.first;
    string1.append(symbol);
    string2.append(symbol);
    debug(prefix_function);
    debug(symbol);
    if (symbol < kAlphabet) {
      int cur_len = prefix_function.back();
      while (string1[cur_len] != symbol && cur_len) {
        cur_len = prefix_function[cur_len];
      }
      if (string1[cur_len] == symbol && string1.size() > 1) {
        ++cur_len;
      } else {
        cur_len = 0;
      }
      prefix_function.push_back(cur_len);
    } else {
      int max_len = 0;
      debug(occurences[symbol]);
      for (int o : occurences[symbol]) {
        int begin = string1.size() - o - 1;
        assert(string1.size() - begin == o + 1);
        if (string1.hash(0, o + 1) == string1.hash(begin, string1.size()) &&
            string2.hash(0, o + 1) == string2.hash(begin, string1.size())) {
          max_len = max(max_len, o + 1);
        }
      }
      prefix_function.push_back(max_len);
      debug(max_len);
    }
    occurences[symbol].push_back(string1.size() - 1);
    dfs(&(node->tranistions[symbol]));
    prefix_function.pop_back();
    string1.pop_back();
    string2.pop_back();
    occurences[symbol].pop_back();
  }
}

int main() {
  occurences.resize(1000 * 1000 + 1);
  std::ios_base::sync_with_stdio(false);
  int n;
  cin >> n;
  map<int, int> stat;
  std::vector<Request> requests;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (s == "-") {
      requests.emplace_back();
      requests.back().action = Request::Remove;
    } else {
      requests.emplace_back();
      requests.back().action = Request::Add;
      cin >> requests.back().symbol;
      stat[requests.back().symbol] += 1;
    }
  }
  std::vector<pii> alphabet_sorted_by_occurences;
  for (const auto &kv : stat) {
    alphabet_sorted_by_occurences.emplace_back(kv.second, kv.first);
  }
  sort(all(alphabet_sorted_by_occurences));
  reverse(all(alphabet_sorted_by_occurences));
  debug(alphabet_sorted_by_occurences);
  vector<int> alphabet_permutation(1000 * 1000 + 1, -1);

  for (size_t i = 0; i < alphabet_sorted_by_occurences.size(); ++i) {
    alphabet_permutation[alphabet_sorted_by_occurences[i].second] = (int)i;
  }
  for (auto &r : requests) {
    if (r.action == Request::Add) {
      r.symbol = alphabet_permutation[r.symbol];
    }
  }

  TrieNode root;
  TrieNode *cur_node = &root;
  for (int i = 0; i < n; ++i) {
    const auto &r = requests[i];
    if (r.action == Request::Remove) {
      cur_node = cur_node->parent;
    } else {
      auto ne = &(cur_node->tranistions[r.symbol]);
      ne->parent = cur_node;
      cur_node = ne;
    }
    cur_node->requests_ids.push_back(i);
  }
  ans.assign(n, -1);
  prefix_function.push_back(0);
  // dfs(&root);

  stack<pair<TrieNode *, typename map<int, TrieNode>::const_iterator>>
      to_process;
  to_process.emplace(&root, root.tranistions.begin());
  while (!to_process.empty()) {
    auto node = to_process.top().first;
    auto it = to_process.top().second;
    if (it == node->tranistions.begin()) {
      for (int r : node->requests_ids) {
        ans[r] = prefix_function.back();
      }
    } else {
      prefix_function.pop_back();
      string1.pop_back();
      string2.pop_back();
      occurences[std::prev(it)->first].pop_back();
    }
    if (it != node->tranistions.end()) {
      const int symbol = it->first;
      string1.append(symbol);
      string2.append(symbol);
      if (symbol < kAlphabet) {
        int cur_len = prefix_function.back();
        while (string1[cur_len] != symbol && cur_len) {
          cur_len = prefix_function[cur_len];
        }
        if (string1[cur_len] == symbol && string1.size() > 1) {
          ++cur_len;
        } else {
          cur_len = 0;
        }
        prefix_function.push_back(cur_len);
      } else {
        int max_len = 0;
        debug(occurences[symbol]);
        for (int o : occurences[symbol]) {
          int begin = string1.size() - o - 1;
          assert(string1.size() - begin == o + 1);
          if (string1.hash(0, o + 1) == string1.hash(begin, string1.size()) &&
              string2.hash(0, o + 1) == string2.hash(begin, string1.size())) {
            max_len = max(max_len, o + 1);
          }
        }
        prefix_function.push_back(max_len);
        debug(max_len);
      }
      occurences[symbol].push_back(string1.size() - 1);
      ++to_process.top().second;
      to_process.emplace(&(node->tranistions[symbol]),
                         node->tranistions[symbol].tranistions.begin());

    } else {
      to_process.pop();
    }
  }

  for (int a : ans) {
    cout << a << "\n";
  }

  if (0) {
    vi s;
    for (int i = 0; i < n; ++i) {
      if (requests[i].action == Request::Remove) {
        s.pop_back();
      } else {
        s.push_back(requests[i].symbol);
      }
      int a_i = 0;
      for (int len = 1; len < (int)s.size(); ++len) {
        if (std::equal(s.begin(), s.begin() + len, s.end() - len)) {
          a_i = len;
        }
      }
      debug(i);
      assert(a_i == ans[i]);
    }
  }

  return 0;
}
