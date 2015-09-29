#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <cstring>
#include <cstdlib>
#include <map>
#define f first
#define s second
#define ll long long
#define ull unsigned long long
#define mp make_pair
#define pb push_back
#define vi vector <int>
#define pii pair<int , int>
using namespace std;
const int N =4005;
const ll inf = (ll)(1e14);
pair <ll,ll> line[N][N];
int n,T;
int f[N],t[N],p[N];
pair <int, pii> a[N];
int sz[N];
ll dp[N];
int k;
double x1,x2;
int lnk[N];

void add(int i,pair <ll,ll> p){
        k = sz[i];
        while(k > 1){
                x1 = (line[i][k-1].s - line[i][k].s + 0.0) / (line[i][k].f - line[i][k-1].f);
                x2 = (line[i][k].s - p.s + 0.0) / (p.f - line[i][k].f);
                if(x1 < x2) break;
                if(k == lnk[i]) lnk[i]--;
        k--;
        }
        line[i][++k] = p;
        sz[i] = k;
}

ll find_max(int i,int x){
        if(sz[i] == 0) return -inf;
        k = min(lnk[i],sz[i]);
        while(k < sz[i]){
                if(line[i][k].s - line[i][k+1].s >= x * (line[i][k+1].f - line[i][k].f)) break;
                k++;
        }
        lnk[i] = k;
        return line[i][k].f * x + line[i][k].s;

}

int main () {
        scanf("%d%d",&n,&T);
        for(int i=1;i<=n;i++){
                scanf("%d%d%d",&t[i],&p[i],&f[i]);
                a[i] = mp(f[i],mp(t[i],p[i]));
        }
        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++){
                f[i] = a[i].f;
                t[i] = a[i].s.f;
                p[i] = a[i].s.s;
        }
        for(int i=1;i<=T;i++) lnk[i] = 1;

        ll res;
        ll ans =0;
        for(int i=1;i<=n;i++){
                if(t[i] > T) continue;
                dp[t[i]] = p[i];
                for(int j=t[i]+1;j<=T;j++){
                        res = find_max(j - t[i],f[i]);
                        if(res == -inf){
                                 dp[j] = -inf;
                                 continue;
                        }
                        dp[j] = res + p[i] - f[i] * f[i];
                }
                for(int j=t[i];j<=T;j++){
                        ans = max(ans,dp[j]);
                    if(dp[j] != -inf) add(j, mp(2*f[i],dp[j] - f[i] * f[i]));
                }
        }
        cout << ans << "\n";


return 0;
}
