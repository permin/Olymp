#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <limits>
#include <numeric>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

#define MP make_pair
#define all(v) (v).begin(), (v).end()
#define PROBLEM_ID "preventing"

typedef long long ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<bool> vb;
typedef long long ll;
typedef pair<int, int> pii;

const int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113};
const int PRIMES_COUNT = 30;
const int MAX_USED = 121;


int SolutionSlow(const vi& a, int k) {
  int n = a.size();
  vi b(n);
  for (int i = 0; i < n; ++i) {
    b[i] = (a[i] + k - 1) / k;
  }
  sort(b.begin(), b.end());
  vector<int> masks(MAX_USED + 1, 0);
  masks[0] = (1 << PRIMES_COUNT) - 1;
  for (int i = 2; i <= MAX_USED; ++i) {
    for (int j = 0; j < PRIMES_COUNT; ++j) {
      if (i % PRIMES[j] == 0) {
        masks[i] |= (1 << j);
      }
    }
  }
  const int INF = 1000000000;
  vector<map<int, int> > min_sums(a.size() + 1);
  min_sums[0][0] = 0;
  for (int pos = 0; pos < a.size(); ++pos) {
    for (map<int, int>::const_iterator it = min_sums[pos].begin(); it != min_sums[pos].end(); ++it) {
      int mask = it->first;
      int cur_sum = it->second;
      for (int new_value = b[pos]; new_value < MAX_USED; ++new_value) {
        if ((masks[new_value] & mask) == 0) {
          int new_mask = (mask | masks[new_value]);
          if (min_sums[pos + 1].count(new_mask) == 0) {
            min_sums[pos + 1][new_mask] = cur_sum + new_value;
          } else {
            min_sums[pos + 1][new_mask] = min(min_sums[pos + 1][new_mask], cur_sum + new_value);
          }
        }
      }
    }
  }
  int result = INF;
  for (map<int, int>::const_iterator it = min_sums[a.size()].begin(); it != min_sums[a.size()].end(); ++it) {
    result = min(result, it->second);
  }
  result *= k;
  for (int i = 0; i < n; ++i) {
    result -= a[i];
  }
  return result;
}

int SolutionFast(const vi& a, int k) {
  int n = a.size();
  vi b(n);
  for (int i = 0; i < n; ++i) {
    b[i] = (a[i] + k - 1) / k;
  }
  sort(b.begin(), b.end());
  vb is_prime(1000, false);
  for (int i = 0; i < PRIMES_COUNT; ++i) {
    is_prime[PRIMES[i]] = true;
  }
  vector<int> masks(MAX_USED + 1, 0);
  masks[0] = (1 << PRIMES_COUNT) - 1;
  for (int i = 2; i <= MAX_USED; ++i) {
    for (int j = 0; j < PRIMES_COUNT; ++j) {
      if (i % PRIMES[j] == 0) {
        masks[i] |= (1 << j);
      }
    }
  }
  const int INF = 1000000000;
  vector<map<pii, int> > min_sums(a.size() + 1);
  min_sums[0][MP(0, 0)] = 0;
  for (int pos = 0; pos < a.size(); ++pos) {
    for (map<pii, int>::const_iterator it = min_sums[pos].begin(); it != min_sums[pos].end(); ++it) {
      int mask = it->first.first;
      int last = it->first.second;
      int cur_sum = it->second;
      for (int new_value = max(b[pos], last); new_value <= MAX_USED; ++new_value) {
        if ((masks[new_value] & mask) == 0) {
          int new_mask = (mask | masks[new_value]);
          if (min_sums[pos + 1].count(MP(new_mask, new_value)) == 0) {
            min_sums[pos + 1][MP(new_mask, new_value)] = cur_sum + new_value;
          } else {
            min_sums[pos + 1][MP(new_mask, new_value)] = min(min_sums[pos + 1][MP(new_mask, new_value)], cur_sum + new_value);
          }
          if (is_prime[new_value] && new_value >= b.back()) {
            break;
          }
        }
      }
    }
  }
  int result = INF;
  for (map<pii, int>::const_iterator it = min_sums[a.size()].begin(); it != min_sums[a.size()].end(); ++it) {
    result = min(result, it->second);
  }
  result *= k;
  for (int i = 0; i < n; ++i) {
    result -= a[i];
  }
  return result;
}

int main() {
  freopen(PROBLEM_ID".in", "r", stdin);
  freopen(PROBLEM_ID".out", "w", stdout);
  int tests;
  cin >> tests;
  for (int test_index = 0; test_index < tests; ++test_index) {
    int n, k;
    cin >> n >> k;
    vi a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    /*int result = SolutionSlow(a, k);
    cout << "Case #" << test_index + 1 << ": " << result << endl;
    cerr << "Case #" << test_index + 1 << ": " << result << endl;*/
    int result2 = SolutionFast(a, k);
    cout << "Case #" << test_index + 1 << ": " << result2 << endl;
    cerr << "Case #" << test_index + 1 << ": " << result2 << endl;
  }
  return 0;
}
