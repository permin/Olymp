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

int mod_pow(int x, int n, int mod) {
  int r = 1;
  while (n) {
    if (n & 1) {
      n ^= 1;
      r = mul(r, x, mod);
    } else {
      n /= 2;
      x = mul(x, x, mod);
    }
  }
  return r;
}
int inv(int x, int mod) { return mod_pow(x, mod - 2, mod); }

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
  int acutal_hash(int begin, int end) const {
    int h = pref_hashes_[end];
    h = add(h, kMod - pref_hashes_[begin], kMod);
    return mul(h, inv(powers_[begin], kMod), kMod);
  }

 private:
  vi powers_;
  vi symbols_;
  vi pref_hashes_;
  // a_0 + a_1 * b + a_2 * b^2 + ...
};

struct Node {
  map<int, Node> nodes;
  Node *suffix_link = nullptr;
  Node *terminal_link = nullptr;
  int occurences = 0;
  int length = 0;
  int hash = 0;
};

Node oddRoot;
Node evenRoot;

int main() {
  std::ios_base::sync_with_stdio(false);
  oddRoot.length = -1;

  evenRoot.suffix_link = oddRoot.suffix_link = &oddRoot;

  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  Node *cur = &evenRoot;
  vector<Node *> order;
  map<pii, Node *> polys;
  for (int i = 0; i < n; ++i) {
    while (s[i - 1 - cur->length] != s[i]) {
      cur = cur->suffix_link;
    }
    if (cur->nodes.count(s[i]) == 1) {
      cur = &(cur->nodes[s[i]]);
    } else {
      Node *new_node = &((*cur).nodes[s[i]]);
      int old_hash = cur->hash;
      order.push_back(new_node);
      new_node->length = cur->length + 2;
      cur = cur->suffix_link;
      while (s[i - 1 - cur->length] != s[i]) {
        cur = cur->suffix_link;
      }
      if (new_node->length == 1) {
        new_node->suffix_link = &evenRoot;
        new_node->hash = s[i];
      } else {
        static const int B = 100 * 1000 + 1;
        static const int MO = 1000 * 1000 * 1000 + 7;
        new_node->suffix_link = &(cur->nodes.at(s[i]));
        new_node->hash = add(
            add(s[i], mul(mod_pow(B, new_node->length - 1, MO), s[i], MO), MO),
            mul(old_hash, B, MO), MO);
      }
      cur = new_node;
      polys[pii(1 + i - cur->length, cur->length)] = cur;
    }
    debug(cur->length);
    cur->occurences += 1;
  }
  reverse(all(order));
  debug(s);
  for (auto node : order) {
    node->suffix_link->occurences += node->occurences;
  }
  vector<pii> ps;
  for (auto kv : polys) {
    ps.push_back(kv.first);
    debug(s.substr(kv.first.first, kv.first.second));
    debug(kv.second->length);
    debug(kv.second->suffix_link->length);
    debug(kv.second->hash);
    debug(kv.second->occurences);
  }

  HashableString<239, 1000 * 1000 * 1000 + 9> hs;
  for (char ch : s) {
    hs.append(ch);
  }
  sort(all(ps), [&](const pii &a, const pii &b) {
    int a1 = a.first;
    int a2 = a.first + a.second;
    int b1 = b.first;
    int b2 = b.first + b.second;
    // cerr << "Cmp: " << s.substr(a.first, a.second) << " "
    //     << s.substr(b.first, b.second) << "\n";
    if (hs.hash(a1, a2) == hs.hash(b1, b2)) {
      return false;
    }
    int l = 0;
    int r = min(a.second, b.second) + 1;
    while (l + 1 < r) {
      int cand_len = (l + r) / 2;
      if (hs.hash(a1, a1 + cand_len) == hs.hash(b1, b1 + cand_len)) {
        l = cand_len;
      } else {
        r = cand_len;
      }
    }
    debug(l);
    if (l == min(a.second, b.second)) {
      return a.second < b.second;
    }
    return s[a1 + l] < s[b1 + l];
  });

  vector<int> o;
  for (auto xx : ps) {
    debug(s.substr(xx.first, xx.second));
    o.push_back(polys[xx]->occurences);
  }
  vector<ll> skip(1, 0);
  for (int i = 0; i < (int)o.size(); ++i) {
    skip.push_back(skip.back() + o[i]);
  }
  debug(o);
  debug(skip);

  HashableString<1000 * 100 + 1, 1000 * 1000 * 1000 + 7> ans_str;
  for (char ch : s) {
    ans_str.append(ch);
  }

  /*vector<string> polyndroms_for_st;
  {
    vector<string> ps;
    for (int i = 0; i < (int)s.size(); ++i) {
      for (int j = i + 1; j <= (int)s.size(); ++j) {
        string sb = s.substr(i, j - i);
        string rsb = sb;
        reverse(all(rsb));
        if (rsb == sb) {
          ps.push_back(sb);
        }
      }
    }
    sort(all(ps));
    polyndroms_for_st = ps;
  }*/
  while (q-- > 0) {
    ll req;
    cin >> req;
    --req;
    auto it = std::upper_bound(all(skip), req);
    if (it == skip.end()) {
      // assert((int)polyndroms_for_st.size() <= req);
      cout << "-1\n";
      continue;
    }
    int i = int(it - skip.begin());
    --i;
    // assert(s.substr(ps[i].first, ps[i].second) == polyndroms_for_st[req]);
    // int ans_hash = ans_str.acutal_hash(ps[i].first, ps[i].first +
    // ps[i].second);
    // assert(polys[ps[i]]->hash == ans_hash);
    cout << ans_str.acutal_hash(ps[i].first, ps[i].first + ps[i].second)
         << "\n";
    // s.substr(ps[i].first, ps[i].second) << "\n";
  }

  return 0;
}
