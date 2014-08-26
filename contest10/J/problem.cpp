/* Team: moscow04 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include <vector>
#include <deque>
#include <queue>
#include <string>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <iterator>

#include <complex>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <climits>
#include <cassert>

using namespace std;

#define DEBUG

#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)((a).size()))
#define pb push_back
#define MP make_pair
#define mp MP

#ifdef DEBUG
    #define debug(x) cerr << #x << ": " << (x) << endl;
#else
    #define debug(x) ;
#endif

typedef pair<int, int> pii;
typedef long long ll;

template <typename T> T sqr (T x) {return x * x;}
template <typename T> T abs (T x) {return x > 0 ? x : -x;}

template <typename T>
ostream & operator << (ostream & out, vector<T> const & a) {
    out << "[";
    for (int i = 0; i < sz(a); ++i) {
        if (i != 0) {
            out << ", ";
        }
        out << a[i];
    }
    out << "]";
    return out;
}

template <typename T1, typename T2>
ostream & operator << (ostream & out, pair<T1, T2> const & p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

void showTime () {
#ifdef DEBUG
    static double prev;
    static bool first = true;

    double curr = (double)clock() / CLOCKS_PER_SEC;

    cerr.setf(ios::fixed);
    cerr.precision(3);
    cerr << "<";
    if (!first) {
        cerr << curr - prev << "sec, ";
    }
    cerr << curr << "sec>\n";

    first = false;
    prev = curr;
#endif
}

bool err;

void NoS() {
    assert(!err);
    cout << "No Solution\n";
}

void MulS() {
    assert(!err);
    cout << "Multiple Solutions\n";
}

ll gcd (ll a, ll b, ll & x, ll & y) {
    if (b == 0) {
        ll d = a;
        x = 1;
        y = 0;
        return d;
    }
    else {
        ll x1, y1;
        ll d = gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - (a / b) * y1;
        return d;
    }
}


int main () {

    if (0) {
        ll x,y;

        debug(gcd(16, 6, x, y));
        debug(x);
        debug(y);
        return 0;
    }

    //freopen("input.txt" , "r" , stdin);
    int tests=100500;;
    cin >> tests;
    for (int test = 0;  test < tests; ++test) {
        err = false;
        cout << "Case #" << (test + 1) << ":\n";
        int n, w;
        if ((cin >> n >> w).eof()) {
            break;
        }
        vector<int> a(w + 1);
        for (int i = 0; i <= w; ++i) {
            cin >> a[i];
        }
        //debug(n);
        //debug(w);
        //debug(a);
        int mi = 1e9;
        bool f = 0;
        // legs count
        vector<int> legs;
        vector<int> number;
        for (int i = 0; i < w; ++i) {
            if (a[i] - a[i + 1] > mi) {
                f = 1;
            };
            if (mi == a[i]-a[i+1]) {
                /*legs.pop_back();
                number.pop_back();

                legs.push_back(0);
                number.push_back(0);*/
            }
            mi = min(mi, a[i]-a[i+1]);
            legs.push_back(i+1);
            number.push_back(a[i]-a[i+1]);
        }
        if (f || mi < 0) {
            NoS();
            continue;
        }

        //fix numbers
        for (size_t i = 0; i + 1 < number.size(); ++i) {
            number[i] -= number[i + 1];
        }

        int foundWithLast = 0;
        int foundWithOutLast = 0;

        int animalsDetermined = 0;

        for (size_t i = 0; i < legs.size(); ++i) {
            if (number[i] > 0) {
                ++foundWithLast;
                if (i + 1 != legs.size()) {
                    ++foundWithOutLast;
                    animalsDetermined += number[i];
                }
            }
        }

        if (foundWithLast > n) {
            NoS();
            continue;
        }

        if (number.back() == 0) {
            if (foundWithLast != n) {
                NoS();
                continue;
            } else {
                /*int out = 0;
                cout << "Unique Solution\n";
                for (size_t i = 0; i + 1 < legs.size(); ++i) {
                    if (number[i]) {
                        cout << legs[i] << " " << number[i] << "\n";
                        ++out;
                    }
                }
                assert(out == n);
                continue;*/
            }
        }

        int K = n - foundWithOutLast;

        int B = w;
        //debug(K);
        //debug(B);
        vector<int> c;
        for (int i = 0; i <= B; ++i) {
            c.push_back(a[i]);
        }

        int substr = 0;
        int sum = 0;

        for (int i = int(number.size()) - 2; i >= 0; --i) {
            sum += number[i];
            substr += sum;
            c[i] -= substr;
            //assert(c[i] >= 0);
            if (c[i] < 0)
                f = 1;
        }
        if (f) {
            NoS();
            continue;
        }
        //debug(c);
        /*for (int i = 0; i + 1 < number.size(); ++i) {
            for (int j = 0; j + 1 < number.size(); ++j) {
                c[i] -= max(legs[j] - i, 0) * number[j];
            }
        }*/

        f = 0;
        int S1 = c.back();
        int S2 = -1;
        if ((c[0] - S1) < 0 || (c[0] - S1) % B) {
            f = 1;
        }
        if (f) {
            NoS();
            continue;
        }
        S2 = (c[0] - S1) / B;
        for (int i = 0; i <= B; ++i) {
            if (S1 + 1LL * (B - i) * S2 != c[i]) {
                f = 1;
                break;
            }
        }
        if (K == 0) {
            f = !(S1 == 0 && S2 == 0);
        }
        if (f) {
            NoS();
            continue;
        }
        //debug(S1);
        //debug(S2);

        if (K == 2) {
            int solutions = 0;
            assert(S1 < 100);
            assert(S2 < 100);
            for (int x = 0; x < 100; ++x){
                for (int y = 0; y < 100; ++y) {
                    for (int n0 = 1; n0 < 100; ++n0) {
                        if (x == y)
                            continue;
                        int n1 = S2 - n0;
                        if (n1 < 1)
                            continue;
                        if (x * n0 + y * n1 == S1)
                            ++solutions;
                    }
                }
            }
            assert((solutions & 1) == 0);
            //debug(solutions/2);
            solutions /= 2;
            if (solutions == 0) {
                NoS();continue;
            }
            if (solutions > 1) {
                MulS();continue;
            }
            err = true;
        }

        if (S2 < K) {
            NoS();
            continue;
        }
        int M1 = (K - 1) * K / 2;
        vector<int> N;
        vector<int> x;
        if (K == 1) {
            N.push_back(S2);
            if (S1 % N[0]) {
                NoS();
                continue;
            }
            x.push_back(S1 / N[0]);
        } else if (K >= 2) {
            if (M1 > S1) {
                NoS();
                continue;
            }
            if (M1 == S1) {
                for (int i = 0; i < K; ++i)
                    x.push_back(i);
                N.push_back(S2 - (K-1));
                assert(N.back() > 0);
                for (int i = 1; i < K; ++i)
                    N.push_back(1);
            }
            if (S1 == M1 + 1) {
                if (S2 > K) {
                    MulS();
                    continue;
                }
                for (int i = 0; i < K; ++i)
                    x.push_back(i);
                ++x.back();
                for (int i = 0; i < K; ++i)
                    N.push_back(1);
            }
            if (S1 > M1 + 1) {
                if (K == 2) {
                    set<pii> xs;
                    int lasrN0 = -1;
                    for (int n0 = 1; n0 < S2; ++n0) {
                        int A = n0;
                        int B = S2;
                        int C = S1;

                        // x < 0
                        // y >= 0

                        ll x0, y0;
                        ll d = gcd(A, B, x0, y0);
                        if (C % d) {
                            continue;
                        }

                        A /= d;
                        B /= d;
                        C /= d;

                        x0 *= C;
                        y0 *= C;

                        int t0 = - x0 / B;
                        int t1 = y0 / A;
                        int t2 = A == B ? 0 : (x0 + y0) / (B - A);

                        for (int delta = -5; delta <= +5; ++delta) {
                            int t_ = t0 + delta;
                            if (x0 + B * t_ < 0 && y0 - t_ * A >= 0 &&
                                  x0 + B * t_ + y0 - t_ * A  >= 0) {
                                xs.insert(pii((x0 + B * t_)  +  y0 - t_ * A,  y0 - t_ * A));
                                lasrN0 = n0;
                            }
                        }

                        for (int delta = -5; delta <= +5; ++delta) {
                            int t_ = t1 + delta;
                            if (x0 + B * t_ < 0 && y0 - t_ * A >= 0 &&
                                  x0 + B * t_ + y0 - t_ * A  >= 0) {
                                xs.insert(pii((x0 + B * t_)  +  y0 - t_ * A,  y0 - t_ * A));
                                lasrN0 = n0;
                            }
                        }

                        for (int delta = -5; delta <= +5; ++delta) {
                            int t_ = t2 + delta;
                            if (x0 + B * t_ < 0 && y0 - t_ * A >= 0 &&
                                  x0 + B * t_ + y0 - t_ * A  >= 0) {
                                xs.insert(pii((x0 + B * t_)  +  y0 - t_ * A,  y0 - t_ * A));
                                lasrN0 = n0;
                            }
                        }
                    }
                    if (xs.empty()) {
                        NoS();
                        continue;
                    }
                    if (xs.size() >= 2) {
                        //debug(xs.size());
                        //for (auto xxx: xs)
                        //    debug(xxx);
                        MulS();
                        continue;
                    } else {
                        x.push_back(xs.begin()->first);
                        x.push_back(xs.begin()->second);
                        N.push_back(lasrN0);
                        N.push_back(S2 - lasrN0);
                        //debug(x);
                        //debug(N);
                        assert(x[0] * N[0] + x[1] * N[1] == S1);

                        //cout << lasrN0 << " " << S2 - lasrN0 << " " << xs.begin()->first << " " <<
                    }
                } else {
                    MulS();
                    continue;
                }
            }
        }

        cout << "Unique Solution\n";

        // Out numbers
        vector<int> whatWeSee(w + 1, -1);
        {
            int out = 0;
            vector<int> a, b;
            for (size_t i = 0; i+ 1 < legs.size(); ++i) {
                if (number[i]) {
                    ++out;
                    cout << legs[i] << " " << number[i] << "\n";
                    a.push_back(legs[i]);
                    b.push_back(number[i]);
                }
            }
            assert(legs.back() <= B);
            for (int i = 0; i < K; ++i) {
                ++out;
                assert(x[i]>=0);
                cout << B + x[i] << " " << N[i] << "\n";
                a.push_back(B + x[i]);
                b.push_back(N[i]);
            }
            assert(out == n);
            assert(is_sorted(all(a)));

            for (int i = 0; i <= w; ++i) {
                whatWeSee[i] = 0;
                for (size_t j = 0; j < a.size(); ++j) {
                    whatWeSee[i] += a[j] * b[j];
                    if (a[j])
                        --a[j];
                }
            }
        }
        assert(whatWeSee == a);
    }
    return 0;
}

