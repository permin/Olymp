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

template <class It>
bool matches(It pattern_begin, It pattern_end, It input_begin, It input_end,
             map<char, string> &defined_characters, set<string> &words_used) {
  if (std::distance(pattern_begin, pattern_end) >
      std::distance(input_begin, input_end)) {
    return false;
  }
  if (pattern_begin == pattern_end) {
    return input_begin == input_end;
  }
  char first_char = *pattern_begin;
  if (defined_characters.count(first_char)) {
    const string &first_word = defined_characters.at(first_char);
    if (first_word.size() <= std::distance(input_begin, input_end) &&
        std::equal(first_word.begin(), first_word.end(), input_begin)) {
      return matches(std::next(pattern_begin), pattern_end,
                     std::next(input_begin, first_word.size()), input_end,
                     defined_characters, words_used);
    }
  } else {
    It end_of_first_word = input_begin;
    do {
      ++end_of_first_word;
      const string first_word = std::string(input_begin, end_of_first_word);
      if (words_used.count(first_word) > 0) {
        continue;
      }
      defined_characters[first_char] = first_word;
      words_used.insert(first_word);
      if (matches(std::next(pattern_begin), pattern_end, end_of_first_word,
                  input_end, defined_characters, words_used)) {
        return true;
      }
      defined_characters.erase(first_char);
      words_used.erase(first_word);
    } while (end_of_first_word != input_end);
  }
  return false;
}

int wordpattern(string pattern, string input) {
  map<char, string> defined_characters;
  set<string> words_used;
  bool res = matches(pattern.begin(), pattern.end(), input.begin(), input.end(),
                     defined_characters, words_used);
  debug(defined_characters);
  return res;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  string p, i;
  cin >> p >> i;
  cout << wordpattern(p, i) << "\n";
  return 0;
}
