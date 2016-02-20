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

template <class T> class IsIterable__ {
  static void f(...);
  template <class U> static typename U::const_iterator f(const U &);

public:
  const static bool value =
      !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S>
ostream &operator<<(ostream &o, const pair<F, S> &p) {
  return o << "(" << p.first << ", " << p.second << ")";
}

template <class C> void O__(ostream &o, const C &c) {
  bool f = 1;
  for (const auto &x : c) {
    if (!f)
      o << ", ";
    if (IsIterable__<decltype(x)>::value)
      o << "\n";
    f = 0;
    o << x;
  }
}

template <class T> ostream &operator<<(ostream &o, const vector<T> &v) {
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

template <class T> ostream &operator<<(ostream &o, const set<T> &v) {
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

/*struct Task {
  int process_time;
  int arrival_time;
};

enum TaskStatus { Recieve, Complete };

struct ProcessingTaskEvent {
  int time;
  TaskStatus status;
  int task_id;
};

bool operator<(const ProcessingTaskEvent &e1, const ProcessingTaskEvent &e2) {
  if (e1.time != e2.time) {
    return e1.time < e2.time;
  }
  if (e1.status != e2.status) {
    return e1.status < e2.status;
  }
  return e1.task_id < e2.task_id;
}

vector<int> find_completion_time(const vector<Task> &tasks, int processors) {
  vi tasts_completion_times(tasks.size(), -1);

  multiset<ProcessingTaskEvent> events;
  for (int i = 0; i < static_cast<int>(tasks.size()); ++i) {
    events.emplace(tasks[i].arrival_time, TaskStatus::Recieve, i);
  }
  int processors_free = processors;
  deque<int> delayed_unprocessed_tasks;
  while (!events.empty()) {
    const ProcessingTaskEvent event = *events.begin();
    events.erase(events.begin());
    if (event.status == Recieve) {
      const Task &task = tasks[event.task_id];
      if (processors_free > 0) {
        events.emplace(task.arrival_time + task.process_time,
                       TaskStatus::Complete, event.task_id);
        --processors_free;
      } else {
        delayed_unprocessed_tasks.push_back(event.task_id);
      }
    } else if (event.status == Complete) {
      tasts_completion_times[event.task_id] = event.time;
      ++processors_free;
      if (!delayed_unprocessed_tasks.empty()) {
        --processors_free;
        const Task &task = tasks[delayed_unprocessed_tasks.front()];

        events.emplace(event.time + task.process_time, TaskStatus::Complete,
                       delayed_unprocessed_tasks.front());

        delayed_unprocessed_tasks.pop_front();
      }
    }
  }
  assert(delayed_unprocessed_tasks.empty());
  return tasts_completion_times;
}*/

/*vi find_completion_times(vi tasks_arrival_times, vi processors_work_duration)
{
  sort(all(tasks_arrival_times));
  sort(all(processors_work_duration));

  set<int> free_processors;
  set<pii> processor_release_times;
  int current_time = 0;
  for (int i = 0; i < static_cast<int>(processors_work_duration.size()); ++i) {
    free_processors.insert(i);
  }

  vi completion_times(tasks_arrival_times.size(), -1);
  for (size_t i = 0; i < tasks_arrival_times.size(); ++i) {
    current_time = max(current_time, tasks_arrival_times[i]);
    while (!processor_release_times.empty() &&
           processor_release_times.begin()->first <= current_time) {
      free_processors.insert(processor_release_times.begin()->second);
      processor_release_times.erase(processor_release_times.begin());
    }
    if (free_processors.empty()) {
      free_processors.insert(processor_release_times.begin()->second);
      current_time = processor_release_times.begin()->first;
      processor_release_times.erase(processor_release_times.begin());
    }

    int processor_id = *free_processors.begin();
    free_processors.erase(free_processors.begin());
    completion_times[i] = current_time + processors_work_duration[processor_id];
    processor_release_times.emplace(completion_times[i], processor_id);
  }
  return completion_times;
}*/

void solve_test() {
  int loads_number, washing_machines, dryers, dry_time;
  cin >> loads_number >> washing_machines >> dryers >> dry_time;
  vi wash_time(washing_machines);
  for (int &x : wash_time) {
    cin >> x;
  }
  vi wash_tasks_arrival_times(loads_number, 0);
  vi dry_tasks_arrival_times =
      find_completion_times(wash_tasks_arrival_times, wash_time);
  vi dry_times(dryers, dry_time);
  vi dry_tasks_completions_time =
      find_completion_times(dry_tasks_arrival_times, dry_times);
  cout << *max_element(all(dry_tasks_completions_time));
}

int main() {
  std::ios_base::sync_with_stdio(false);
  size_t test_number = 0;
  cin >> test_number;
  for (size_t test_index = 0; test_index < test_number; ++test_index) {
    cout << "Case #" << test_index + 1 << ": ";
    solve_test();
    cout << "\n";
  }
  return 0;
}
