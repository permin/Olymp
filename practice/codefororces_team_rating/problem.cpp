#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <algorithm>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

long double getWinProbability(long double ra, long double rb) {
    return 1.0 / (1.0 + pow((long double) 10.0, (rb - ra) / 400.0));
}

long double aggregateRatings(vector<long double> teamRatings)
{
    long double left = 1;
    long double right = 1E4;

    for (int tt = 0; tt < 100; tt++) {
        long double r = (left + right) / 2.0;

        long double rWinsProbability = 1.0;
        forn(i, teamRatings.size())
            rWinsProbability *= getWinProbability(r, teamRatings[i]);

        long double rating = log10(1 / (rWinsProbability) - 1) * 400 + r;

        if (rating > r)
            left = r;
        else
            right = r;
    }

    return (left + right) / 2.0;
}

int main()
{
    cout << aggregateRatings({2000,2000}) << "\n";
    cout << aggregateRatings({1000,1000}) << "\n";
    cout << getWinProbability(1000,2000) << "\n";
    cout << getWinProbability(
             aggregateRatings({1000,1000}),
             aggregateRatings({2000,2000})) << "\n";


    vector<long double> a = {2200, 2200};

    printf("%.10lf\n", double(aggregateRatings(a)));
    return 0;
}
