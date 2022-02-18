
// https://cses.fi/problemset/task/1196
// Flight Routes

// 本題要求前 k 個最短路徑, 所以我們不能用 visited[] 卡關,
// 要用每個點最多只能從 priority_queue pop 出 k 次來卡關.

#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <algorithm>

typedef long long ll;
typedef std::pair<ll, ll> pll;

const ll inf = LLONG_MAX;
const ll maxn = (ll)1e5 + 5;
std::vector<pll> edge[maxn];

// 每個點從 priority_queue pop 出幾次.
ll cnt[maxn];

int main () {
    ll n, m, k;
    (void)!scanf("%lld %lld %lld", &n, &m, &k);
    for (ll i = 0; i < m; i++) {
        ll a, b, c;
        (void)!scanf("%lld %lld %lld", &a, &b, &c);
        edge[a].emplace_back(b, c);
    }

    std::priority_queue<pll, std::vector<pll>, std::greater<pll>> q;
    q.emplace(0, 1);
    
    std::vector<ll> ans;

    while (!q.empty()) {
        ll node = q.top().second;
        ll len = q.top().first;
        q.pop();
        if (node == n) {
            // 根據實驗結果, len 值自然會由小而大出現...
            ans.push_back(len);
            if ((ll)ans.size() == k) break;
        }
        // 前 k 個最短路徑, 路徑上的個別 node 最多只會從 priority_queue pop 出 k 次.
        if (cnt[node] == k) continue;
        cnt[node]++;
        for (const pll& x : edge[node]) {
            q.emplace(len + x.second, x.first);
        }
    }

    // 根據實驗結果, 不 sort 也會 AC...
    std::sort(ans.begin(), ans.end());
    for (ll i = 0; i < k; i++) {
        printf("%lld%c", ans[i], i == k ? '\n' : ' ');
    }
}
