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
#include <unordered_map>
#include <functional>
#include <bitset>
#include <valarray>

using namespace std;

#define all(v) (v).begin(), (v).end()
#define MP make_pair
#define debug(x) cerr << #x << ": "  << (x) << "\n";

template <class F, class S> ostream& operator << (ostream& o, const pair<F,S>& p) {
return o << "(" << p.first << ", " << p.second << ")";}

template<class C>void O__(ostream& o, const C& c) {
bool f = 1; for(const auto& x: c) {if (!f) o << ", "; f = 0; o << x;}}

template <class T>
ostream& operator << (ostream& o, const vector<T>& v) {o << "[";O__(o, v);o << "]";return o;}

template <class T, class V>
ostream& operator << (ostream& o, const map<T, V>& v) {o << "{";O__(o, v);o << "}"; return o;}

template <class T>
ostream& operator << (ostream& o, const set<T>& v) {o << "{";O__(o, v);o << "}";return o;}

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

typedef vii Image;

class Class{
public:
    vii read(const vi& data, int& pos) {
        int h = data[pos++];
        int w = data[pos++];
        vii res(h, vi(w, -1));
        for (int i = 0; i < h; ++i)
            for (int j = 0; j < w; ++j) {
                res[i][j] = data[pos++];
            }
        return res;
    }
    Image rescale(const Image& image, int h, int w) {
        assert(h <= image.size() && w <= image[0].size());
        //Image temp(h * image.size(), vi(w * iamge[0].size(), -1));
        vector<vector<double>> sum(h, vector<double>(w, 0.0));
        Image num(h, vi(w, 0));
        for (int i = 0; i < image.size(); ++i)
            for (int j = 0; j < image[i].size(); ++j) {
                for (int x = 0; x < h; ++x)
                    for (int y = 0; y < w; ++y) {
                        //temp[i * h + x][j * w + y] = image[i][j];
                        sum[(i * h + x) / image.size()][(j * w + y) / image[0].size()] += image[i][j];
                        num[(i * h + x) / image.size()][(j * w + y) / image[0].size()] += 1;
                    }
            }
        Image res(h, vi(w, -1));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                res[i][j] = int(0.50000001 + sum[i][j] / num[i][j]);
            }
        }
        return res;
    }
    double getDiff(int i, int j, int dh, int dw) {

    }
    vi solve(vi data) {
        int pos = 0;
        Image target = read(data, pos);
        vector<Image> images;
        int area = 0;
        for (int i = 0; i < 200; ++i) {
            images.push_back(read(data, pos));
            //cerr << images.back().size() << " " << images.back()[0].size() << ", ";
            area += images.back().size() * images.back()[0].size();
        }
        assert(pos == data.size());

        debug(target.size());
        debug(target[0].size());
        vi result(800, -1);
        result[3] = target[0].size() - 1;
        int topLine = 0;
        while (topLine < target.size()) {
            for (int h = 1; h <= 100; ++h) {

            }
        }
        return result;
    }
};


int main() {
    int n;
    cin >> n;
    vi data(n);
    for (int i = 0; i < n; ++i)
        cin >> data[i];
    vi r = Class().solve(data);
    debug(r);
    for (int i = 0; i < 800; ++i)
        cout << r.at(i) << "\n";
    return 0;
}
