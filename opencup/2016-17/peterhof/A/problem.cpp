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
const double EPS = 1e-15;
const int INF = std::numeric_limits<int>::max();
const long long LLINF = std::numeric_limits<ll>::max();

#if GCC_VERSION > 40900
// supports find_by_order(int) and order_of_key(Key)
template <class Key, class Value>
using MapWithOrderStatistics =
    tree<Key, Value, std::less<Key>, rb_tree_tag /*splay_tree_tag*/,
         tree_order_statistics_node_update>;
#endif

int main() {
  std::ios_base::sync_with_stdio(false);
  int n, S;
  cin >> n >> S;
  vector<int> cardValues(n);
  for (int &x : cardValues) {
    cin >> x;
  }

  vector<double> prob(n);
  for (double &x : prob) {
    cin >> x;
  }

  int maxCardsNum = S / 2 + 2;

  vector<vector<double>> distributionsOverSumsOfKcards(maxCardsNum + 1,
                                                       vector<double>(S + 1));
  distributionsOverSumsOfKcards[0][0] = 1.0;
  {
    for (size_t k = 1; k < distributionsOverSumsOfKcards.size(); ++k) {
      for (int newS = 0; newS <= S; ++newS) {
        for (int i = 0; i < n; ++i) {
          int oldS = newS - cardValues[i];
          if (oldS >= 0) {
            distributionsOverSumsOfKcards[k][newS] +=
                distributionsOverSumsOfKcards[k - 1][oldS] * prob[i];
          }
        }
      }
    }
  }
  debug(distributionsOverSumsOfKcards);
  double totalWinProb = 0.0;
  double totalDrawProb = 0.0;
  double allCases = 0;
  for (int k = 1; k <= maxCardsNum; ++k) {
    for (int firstPlayersCard = 0; firstPlayersCard < n; ++firstPlayersCard) {
      double distributionSum = 0;
      for (int v = S - cardValues[firstPlayersCard] + 1; v <= S; ++v) {
        distributionSum += distributionsOverSumsOfKcards[k - 1][v];
      }
      double probOfPlayersInput = prob[firstPlayersCard] * distributionSum;
      allCases += probOfPlayersInput;
      if (probOfPlayersInput < EPS) {
        continue;
      }
      debug(k);
      debug(cardValues[firstPlayersCard]);
      debug(probOfPlayersInput);
      vector<double> probDealerHasLess(S + 1);
      for (int v = S - cardValues[firstPlayersCard] + 1; v <= S - 1; ++v) {
        probDealerHasLess[v + 1] =
            probDealerHasLess[v] +
            distributionsOverSumsOfKcards[k - 1][v] / distributionSum;
      }

      vector<double> probWin(S + 2, 0.0);
      //
      vector<double> probDraw(S + 2, 0.0);
      for (int hand = S; hand >= 0; --hand) {
        double probWinIfContinue = 0.0;
        double probDrawIfContinue = 0.0;
        for (int i = 0; i < n; ++i) {
          int newHand = hand + cardValues[i];
          if (newHand <= S) {
            probWinIfContinue += prob[i] * probWin[newHand];
            probDrawIfContinue += prob[i] * probDraw[newHand];
          }
        }
        double expIfContinue = 2.0 * probWinIfContinue + probDrawIfContinue;
        double expIfStop = 2.0 * probDealerHasLess[hand] +
                           (hand <= S - cardValues[firstPlayersCard]
                                ? 0.0
                                : distributionsOverSumsOfKcards[k - 1][hand] /
                                      distributionSum);

        if (expIfStop > expIfContinue) {
          probWin[hand] = probDealerHasLess[hand];
          probDraw[hand] =
              distributionsOverSumsOfKcards[k - 1][hand] / distributionSum;
        } else {
          probWin[hand] = probWinIfContinue;
          probDraw[hand] = probDrawIfContinue;
        }
      }
      totalWinProb +=
          probOfPlayersInput * probWin[cardValues[firstPlayersCard]];
      totalDrawProb +=
          probOfPlayersInput * probDraw[cardValues[firstPlayersCard]];
    }
  }

  printf("%0.18lf\n", 2 * totalWinProb + totalDrawProb - 1);

  return 0;
}
