
// sssp (single source shortest paths) using Dial's algorithm.
// It's complexity is O(n).
// Bucket sort is used in this algorithm.
// See https://ithelp.ithome.com.tw/articles/10201707 for bucket sort.
//
// 這種方法必須沒有負邊, 可以有環, 會用到 (最長路徑 + 1) 個陣列元素 (int or ll).

#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>

typedef long long ll;
typedef std::pair<ll, ll> pll;

// 最長路徑, 最大節點數目.
const ll maxn = (ll)1e6 + 5;

std::vector<pll> edge[maxn];
bool vis[maxn];     // visited
ll dis[maxn];       // distance
ll parent[maxn];

// Used by bucket sort.
std::vector<pll> bucket[maxn];

int main () {
    ll n, m, s;     // 點數, 邊數, 起點
    (void)!scanf("%lld %lld %lld", &n, &m, &s);
    for (ll i = 0; i < m; i++) {
        ll a, b, c;     // from, to, weight
        (void)!scanf("%lld %lld %lld", &a, &b, &c);
        edge[a].push_back({b, c});
    }

    memset(parent, -1, sizeof(parent));
    memset(dis, -1, sizeof(dis));
    dis[s] = 0;
    bucket[0].push_back({s, s});    // {node, node's parent}

    for (ll i = 0, idx = 0; i < n; i++) {   // there are n nodes
        while (idx < maxn && bucket[idx].empty()) idx++;
        if (idx == maxn) break;     // 起點有連通的最短路徑都已找完

        for (const pll& x : bucket[idx]) {
            ll node = x.first;
            if (vis[node]) continue;
            vis[node] = true;
            dis[node] = idx;
            parent[node] = x.second;
            for (const pll& y : edge[node]) {
                if (vis[y.first]) continue;
                ll len = dis[node] + y.second;
                bucket[len].push_back({y.first, node});
            }
        }

        idx++;
    }

    // 顯示起點到到各點的距離. 測資的 node 是 1-based. -1 代表沒有連通起點.
    for (ll i = 1; i <= n; i++) printf("%lld ", dis[i]);
    printf("\n");

    // 顯示各點的 parent. 測資的 node 是 1-based.
    for (ll i = 1; i <= n; i++) printf("%lld ", parent[i]);
    printf("\n");
}
