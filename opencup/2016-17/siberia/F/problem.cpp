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

namespace min_cost_max_flow {
const size_t UNDEFINED_VERTEX = static_cast<size_t>(-1);

struct CostFlowNetEdge {
  CostFlowNetEdge()
      : source(UNDEFINED_VERTEX),
        target(UNDEFINED_VERTEX),
        cost(0),
        capacity(0),
        flow(0) {}

  CostFlowNetEdge(size_t source, size_t target, long long cost, size_t capacity)
      : source(source),
        target(target),
        cost(cost),
        capacity(capacity),
        flow(0) {}

  size_t source;
  size_t target;
  long long cost;
  size_t capacity;
  long long flow;
  size_t backEdgeIndex;
};

class MinCostMaxFlowNet {
 public:
  typedef std::vector<CostFlowNetEdge>::iterator Iterator;
  typedef std::vector<CostFlowNetEdge>::const_iterator ConstIterator;

  MinCostMaxFlowNet() : edges_(2) {}

  size_t source() const { return source_; }

  size_t sink() const { return sink_; }

  IteratorRange<Iterator> outgoing_edges(size_t v) {
    return make_range(all(edges_[v]));
  }

  IteratorRange<ConstIterator> outgoing_edges(size_t v) const {
    return make_range(edges_[v].cbegin(), edges_[v].cend());
  }

  Iterator back_edge(const CostFlowNetEdge &edge) {
    return std::next(edges_[edge.target].begin(), edge.backEdgeIndex);
  }

  void add_edge(size_t from, size_t to, size_t capacity, long long cost) {
    edges_[from].push_back(CostFlowNetEdge(from, to, cost, capacity));
    edges_[to].push_back(CostFlowNetEdge(to, from, -cost, 0));

    edges_[from].back().backEdgeIndex = edges_[to].size() - 1;
    edges_[to].back().backEdgeIndex = edges_[from].size() - 1;
  }

  size_t vertices_number() const { return edges_.size(); }

  size_t add_vertex() {
    size_t id = edges_.size();
    edges_.emplace_back();
    return id;
  }

 private:
  static const size_t source_ = 0;
  static const size_t sink_ = 1;
  std::vector<std::vector<CostFlowNetEdge>> edges_;
};

vector<ll> fordBelman(size_t source, size_t /*target*/,
                      const MinCostMaxFlowNet &net,
                      vector<const CostFlowNetEdge *> &prev_edge,
                      const vector<ll> * /*phi*/) {
  size_t vertices = net.vertices_number();
  vector<ll> dist(vertices, LLINF);
  prev_edge.assign(vertices, nullptr);
  dist[source] = 0;
  queue<size_t> Q;
  Q.push(source);
  while (!Q.empty()) {
    size_t v = Q.front();
    Q.pop();
    for (const CostFlowNetEdge &e : net.outgoing_edges(v)) {
      size_t v2 = e.target;
      if (e.capacity > 0) {
        ll newDist = dist[v] + e.cost;
        if (dist[v2] > newDist) {
          dist[v2] = newDist;
          prev_edge[v2] = &e;
          Q.push(v2);
        }
      }
    }
  }
  return dist;
}

vector<ll> dijkstra(size_t source, size_t target, const MinCostMaxFlowNet &net,
                    vector<const CostFlowNetEdge *> &prev_edge,
                    vector<ll> *phi) {
  size_t vertices = net.vertices_number();
  vector<ll> dist(vertices, LLINF);
  prev_edge.assign(vertices, nullptr);
  dist[source] = 0;
  set<pair<ll, size_t>> Q;
  Q.emplace(source, dist[source]);
  while (!Q.empty()) {
    size_t v = Q.begin()->second;
    if (v == target && phi == nullptr) {
      break;
    }
    Q.erase(Q.begin());
    for (const CostFlowNetEdge &e : net.outgoing_edges(v)) {
      size_t v2 = e.target;
      if (e.capacity > 0) {
        ll newDist = phi != nullptr ? (*phi)[v] + dist[v] + e.cost - (*phi)[v2]
                                    : dist[v] + e.cost;
        if (dist[v2] > newDist) {
          Q.erase(make_pair(dist[v2], v2));
          dist[v2] = newDist;
          prev_edge[v2] = &e;
          Q.emplace(dist[v2], v2);
        }
      }
    }
  }
  return dist;
}

size_t push_flow(const std::vector<const CostFlowNetEdge *> &prev_edge,
                 MinCostMaxFlowNet &net) {
  size_t cur = net.sink();
  size_t add = INF;
  while (cur != net.source()) {
    const CostFlowNetEdge *incoming_edge = prev_edge[cur];
    add = min(add, incoming_edge->capacity);
    cur = incoming_edge->source;
  }

  cur = net.sink();
  while (cur != net.source()) {
    // TODO(permin): remove const_cast
    CostFlowNetEdge *incoming_edge =
        const_cast<CostFlowNetEdge *>(prev_edge[cur]);
    incoming_edge->capacity -= add;
    incoming_edge->flow += add;

    auto back_edge = net.back_edge(*incoming_edge);
    back_edge->capacity += add;
    back_edge->flow -= add;

    cur = incoming_edge->source;
  }
  return add;
}

template <class ShortestPathFinder>
size_t minCostMaxFlow(MinCostMaxFlowNet &net, ShortestPathFinder finder,
                      bool potentials_need_hint = true) {
  vector<ll> phi;
  if (potentials_need_hint) {
    vector<const CostFlowNetEdge *> dummy;
    phi = fordBelman(net.source(), net.sink(), net, dummy, /*phi=*/nullptr);
  }
  size_t flow = 0;
  while (true) {
    vector<const CostFlowNetEdge *> prev;
    vector<ll> dist = finder(net.source(), net.sink(), net, prev,
                             potentials_need_hint ? &phi : nullptr);
    if (dist[net.sink()] == LLINF) {
      break;
    }
    ll real_distance = dist[net.sink()];
    if (potentials_need_hint) {
      real_distance -= phi[net.source()];
      real_distance += phi[net.sink()];
    }
    if (real_distance >= 0) {
      break;
    }

    if (potentials_need_hint) {
      for (size_t i = 0; i < dist.size(); ++i) {
        phi[i] += dist[i];
      }
    }
    flow += push_flow(prev, net);
  }
  return flow;
}

}  // namespace min_cost_max_flow

int main() {
  std::ios_base::sync_with_stdio(false);

  return 0;
}
