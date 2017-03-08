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

bool isValidCell(int x, int y) { return 0 <= x && x < 7 && 0 <= y && y < 8; }

bool isUnderAttack(int kingX, int kingY, int maharajahX, int maharajahY) {
  int dist = abs(kingX - maharajahX) + abs(kingY - maharajahY);
  /*if (kingX == maharajahX || kingY == maharajahY ||
      abs(kingX - maharajahX) == abs(kingY - maharajahY)) {
    return true;
  }*/
  if (kingX == maharajahX || kingY == maharajahY) {
    return true;
  }
  return dist <= 3;  // && (kingX != maharajahX || kingY != maharajahY);
}

void processMove(const vector<pii> &initiallKingPositions, int maharajahX,
                 int maharajahY, vector<pii> *resultKingPositions,
                 bool &stalemate) {
  stalemate = false;
  resultKingPositions->clear();
  for (const pii &king : initiallKingPositions) {
    bool hasNeighbours = false;
    for (int dx = -1; dx <= +1; ++dx) {
      for (int dy = -1; dy <= +1; ++dy) {
        if (dx != 0 || dy != 0) {
          int nx = king.first + dx;
          int ny = king.second + dy;
          if (maharajahX == nx && maharajahY == ny) {
            // the king can take the maharajah
            stalemate = true;
            return;
          }
          if (isValidCell(nx, ny) &&
              !isUnderAttack(nx, ny, maharajahX, maharajahY)) {
            hasNeighbours = true;
            resultKingPositions->emplace_back(nx, ny);
          }
        }
      }
    }
    if (!hasNeighbours &&
        !isUnderAttack(king.first, king.second, maharajahX, maharajahY)) {
      stalemate = true;
      return;
    }
  }
  sort(all(*resultKingPositions));
  resultKingPositions->erase(std::unique(all(*resultKingPositions)),
                             resultKingPositions->end());
}

int X, Y;

void req(int maharajahX, int maharajahY) {
  assert(X != maharajahX || Y != maharajahY);
  assert(maharajahX < 8);
  assert(maharajahY < 8);
  assert(maharajahX >= 0);
  assert(maharajahY >= 0);
  assert(isUnderAttack(maharajahX, maharajahY, X, Y));
  cout << char('a' + maharajahX) << (1 + maharajahY) << endl;
  X = maharajahX;
  Y = maharajahY;
#ifdef LOCAL_RUN
#else
  cout.flush();
  int x;
  cin >> x;
  if (x == 1) {
    // assert(0 && "Win");
    exit(0);
  }
  if (x) {
    const int M = 1000 * 1000 * 100;
    auto ptr = new int[M];
    ptr[M - 1] = -1;
    for (;;) {
      ;
    }
    exit(0);
  }
  // df
  assert(x == 0);
#endif
}

void solve(int maharajahX, int maharajahY) {
  X = maharajahX;
  Y = maharajahY;
  vector<pii> positions;
  for (int x = 0; x < 8; ++x) {
    for (int y = 0; y < 8; ++y) {
      if (!isUnderAttack(x, y, maharajahX, maharajahY)) {
        positions.emplace_back(x, y);
      }
    }
  }
  int it = 0;
  while (!positions.empty()) {
    assert(isValidCell(maharajahX, maharajahY));
    assert(it < 45);
    ++it;
    debug(maharajahX);
    debug(maharajahY);
    debug(positions.size());
    int bestMoveX = -1;
    int bestMoveY = -1;
    /*int bestMoveX1 = -1;
    int bestMoveY1 = -1;
    int bestMoveX2 = -1;
    int bestMoveY2 = -1;
    int bestMoveX3 = -1;
    int bestMoveY3 = -1;*/
    int M = 8;
    int M1 = 3;
    int M2 = 1;
    int score = -100;
    if (true) {
      for (int x = 0; x < 8; ++x) {
        for (int y = 0; y < 8; ++y) {
          if (x != maharajahX || y != maharajahY) {
            if (!isUnderAttack(x, y, maharajahX, maharajahY)) {
              continue;
            }
            for (int x1 = 0; x1 < 8; ++x1) {
              for (int y1 = 0; y1 < 8; ++y1) {
                if (abs(x1 - x) + abs(y1 - y) > M) {
                  continue;
                }
                if (x1 != x || y1 != y) {
                  if (!isUnderAttack(x1, y1, x, y)) {
                    continue;
                  }
                  for (int x2 = 0; x2 < 8; ++x2) {
                    for (int y2 = 0; y2 < 8; ++y2) {
                      if (abs(x1 - x2) + abs(y1 - y2) > M1) {
                        continue;
                      }
                      if (x2 != x1 || y2 != y1) {
                        if (!isUnderAttack(x1, y1, x2, y2)) {
                          continue;
                        }
                        for (int x3 = 0; x3 < 8; ++x3) {
                          for (int y3 = 0; y3 < 8; ++y3) {
                            if (abs(x3 - x2) + abs(y3 - y2) > M2) {
                              continue;
                            }
                            if (x2 != x3 || y2 != y3) {
                              if (!isUnderAttack(x3, y3, x2, y2)) {
                                continue;
                              }

                              vector<pii> newPos;
                              bool stalemate = false;
                              processMove(positions, x, y, &newPos, stalemate);
                              if (stalemate) {
                                continue;
                              }
                              vector<pii> newPos2;
                              processMove(newPos, x1, y1, &newPos2, stalemate);

                              if (stalemate) {
                                continue;
                              }
                              vector<pii> newPos3;
                              processMove(newPos2, x2, y2, &newPos3, stalemate);

                              if (stalemate) {
                                continue;
                              }

                              vector<pii> newPos4;
                              processMove(newPos3, x3, y3, &newPos4, stalemate);

                              if (stalemate) {
                                continue;
                              }

                              int curScore = int(positions.size()) -
                                             int(newPos4.size()) + (rand() % 3);
                              if (curScore > score) {
                                score = curScore;
                                bestMoveX = x;
                                bestMoveY = y;
                                /*bestMoveX1 = x1;
                                bestMoveY1 = y1;
                                bestMoveX2 = x2;
                                bestMoveY2 = y2;
                                bestMoveX3 = x3;
                                bestMoveY3 = y3;*/
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    assert(score > -50);
    assert(bestMoveX != -1);
    debug(score);
    maharajahX = bestMoveX;
    maharajahY = bestMoveY;
    req(maharajahX, maharajahY);
    // df
    // int init_size = static_cast<int>(positions.size());
    {
      vector<pii> newPos;
      bool stalemate = false;
      processMove(positions, maharajahX, maharajahY, &newPos, stalemate);
      positions.swap(newPos);
      assert(!stalemate);
    }
    /*maharajahX = bestMoveX1;
    maharajahY = bestMoveY1;
    req(maharajahX, maharajahY);
    {
      vector<pii> newPos;
      bool stalemate = false;
      processMove(positions, maharajahX, maharajahY, &newPos, stalemate);
      positions.swap(newPos);
      assert(!stalemate);
    }
    maharajahX = bestMoveX2;
    maharajahY = bestMoveY2;
    req(maharajahX, maharajahY);
    {
      vector<pii> newPos;
      bool stalemate = false;
      processMove(positions, maharajahX, maharajahY, &newPos, stalemate);
      positions.swap(newPos);
      assert(!stalemate);
    }
    maharajahX = bestMoveX3;
    maharajahY = bestMoveY3;
    req(maharajahX, maharajahY);
    {
      vector<pii> newPos;
      bool stalemate = false;
      processMove(positions, maharajahX, maharajahY, &newPos, stalemate);
      positions.swap(newPos);
      assert(!stalemate);
    }*/
    // assert(init_size - positions.size() == score);
  }
  // assert(false);
}

int main() {
#ifdef LOCAL_RUN
  for (int x = 0; x < 8; ++x) {
    for (int y = 0; y < 8; ++y) {
      double t1 = clock();
      cerr << "================\n";
      cerr << x << " " << y << "\n";
      cerr << "================\n";
      solve(x, y);
      double t2 = clock();
      cerr << (t2 - t1) / CLOCKS_PER_SEC << " sec.\n";
    }
  }
#else
  std::ios_base::sync_with_stdio(false);
  string s;
  cin >> s;
  solve(s[0] - 'a', s[1] - '1');
  return 0;

#endif
  return 0;
}
