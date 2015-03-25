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
#include <utility>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

//using namespace __gnu_pbds;
using namespace std;

#ifdef LOCAL_RUN
#define debug(x) cerr << #x << ": "  << (x) << "\n";
#else
#define debug(x) ;
#endif

#define all(v) (v).begin(), (v).end()
#define MP make_pair

template<class T>
class IsIterable__ {
	static void f(...); template<class U> static typename U::const_iterator f(const U&);
public:const static bool value = !std::is_same<void, decltype(f(std::declval<T>()))>::value;
};

template <class F, class S> ostream& operator << (ostream& o, const pair<F, S>& p) {
	return o << "(" << p.first << ", " << p.second << ")";
}

template<class C>void O__(ostream& o, const C& c) {
	bool f = 1; for (const auto& x : c) { if (!f) o << ", "; if (IsIterable__<decltype(x)>::value) o << "\n"; f = 0; o << x; }
}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) { o << "["; O__(o, v); o << "]"; return o; }

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) { o << "{"; O__(o, v); o << "}"; return o; }

template <class T>
ostream& operator << (ostream& o, const set<T>& v) { o << "{"; O__(o, v); o << "}"; return o; }

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

int powNaive(int x, int n) {
	int r = 1;
	for (int i = 0; i < n; ++i)
		r *= x;
	return r;
}

int phi(int p, int k) {
	return powNaive(p, k - 1) * (p - 1);
}

int mul(ll xx, ll yy, int mod) {
	int x = int(xx % mod);
	int y = int(yy % mod);
	return int((1LL * x * y) % mod);
}

int modPow(int x, ll n, int mod) {
	int res = 1;
	while (n > 0) {
		if (n % 2 == 1) {
			n -= 1;
			res = mul(res, x, mod);
		}
		else {
			n /= 2;
			x = mul(x, x, mod);
		}
	}
	return res;
}

int inverseMod(int x, int p, int k) {
	int mod = powNaive(p, k);
	return modPow(x, phi(p, k) - 1, mod);
}

ll maxPowerPInFact(ll n, int p) {
	ll res = 0;
	while (n > 0) {
		n /= p;
		res += n;
	}
	return res;
}

ll pFree(ll q, int p) {
	while (q % p == 0)
		q /= p;
	return q;
}

int factMod(ll n, int p, int k) {
	if (n == 0)
		return 1;
	int x = powNaive(p, k);
	debug(x);
	int mod = x;
	int pref = 1;
	for (ll q = 1; q <= x; ++q) {
		pref = mul(pref, pFree(q, p), mod);
	}
	int res = modPow(pref, n / x, mod);

	ll beginOfLastBlock = (n / x)*x + 1;
	debug(beginOfLastBlock);
	for (ll i = beginOfLastBlock; i <= n; ++i) {
		res = mul(res, pFree(i, p), mod);
	}
	return mul(res, factMod(n / x, p, k), mod);
}

int add(int x, int y, int mod) {
	x += y;
	if (x >= mod)
		x -= mod;
	return x;
}

int CTO(const vi& p, const vi& k, const vi& residuals) {
	int A = 1;
	for (int i = 0; i < p.size(); ++i) {
		A *= powNaive(p[i], k[i]);
	}

	int ans = 0;
	int mod = A;
	for (int i = 0; i < p.size(); ++i) {
		int a = powNaive(p[i], k[i]);
		debug(a);
		debug(p[i]);
		debug(k[i]);
		debug(A / a);

		int res = 1;
		res = mul(res, modPow(A / a, phi(p[i], k[i]), mod), mod);
		res = mul(res, residuals[i], mod);
		ans = add(res, ans, mod);
	}
	return ans;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int m;
	ll n, k;
	cin >> n >> k >> m;

	vi ps, ks;
	{
		for (int i = 2; i * i <= m; ++i) {
			if (m % i == 0) {
				ps.push_back(i);
				ks.push_back(0);
				while (m % i == 0) {
					m /= i;
					ks.back() += 1;
				}
			}
		}
		if (m > 1) {
			ps.push_back(m);
			ks.push_back(1);
		}
	}

	vi r;
	for (int i = 0; i < ps.size(); ++i) {
		ll upperPdegree = maxPowerPInFact(n, ps[i]);
		ll lowerPdegree = maxPowerPInFact(k, ps[i]) +
			maxPowerPInFact(n - k, ps[i]);
		assert(lowerPdegree <= upperPdegree);
		debug(ps[i]);
		debug(upperPdegree);
		debug(lowerPdegree);

		int upperPkMod = factMod(n, ps[i], ks[i]);

		debug(upperPkMod);

		int mod = powNaive(ps[i], ks[i]);

		int lowerPkMod = mul(
			factMod(k, ps[i], ks[i]),
			factMod(n - k, ps[i], ks[i]),
			mod);
		debug(lowerPkMod);
		int residual = 1;
		residual = mul(residual,
			modPow(ps[i], upperPdegree - lowerPdegree, mod),
			mod);
		residual = mul(residual, upperPkMod, mod);
		residual = mul(residual, inverseMod(lowerPkMod, ps[i], ks[i]), mod);
		r.push_back(residual);
	}
	debug(ps);
	debug(ks);
	debug(r);

	cout << CTO(ps, ks, r) << "\n";

	return 0;
}