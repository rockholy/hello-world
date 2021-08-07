
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

ll n, k;

const int maxn = 1e4;
ll a[maxn];
ll b[maxn];
ll c[maxn];
ll tmp[maxn];

bool pass (ll day) {
    for (ll i = 0; i < n; i++) tmp[i] = a[i] + b[i] * day;
    std::sort(tmp, tmp + n);
    auto it = c;
    ll count = 0;
    for (ll i = 0; i < n; i++) {
        auto it2 = std::lower_bound(it, c + n, tmp[i]);
        if (it2 != c) {
            count++;
            if (count >= k) return true;
            it = it2;
        }
    }
    return false;
}

int main () {
    ll t;
    (void)!scanf("%lld", &t);
    while (t--) {
        (void)!scanf("%lld %lld", &n, &k);
        if (k == 0) {
            printf("0\n");
            continue;
        }
        for (ll i = 0; i < n; i++) (void)!scanf("%lld %lld", &a[i], &b[i]);
        for (ll i = 0; i < n; i++) (void)!scanf("%lld", &c[i]);
        std::sort(c, c + n);

        std::vector<ll> v;
        for (ll i = 0; i < n; i++) if (b[i] == 0) v.push_back(a[i]);
        std::sort(v.begin(), v.end());
        ll weak = (ll)v.size();
        ll strong = n - weak;
        ll win = k - strong;
        if (win > 0) {
            auto it = c;
            for (ll x : v) {
                auto it2 = std::lower_bound(it, c + n, x);
                if (it2 != c) {
                    win--;
                    if (win == 0) break;
                    it = it2;
                }
            }
        }
        if (win > 0) {
            printf("-1\n");
            continue;
        }

        if (pass(0)) {
            printf("0\n");
            continue;
        }

        std::vector<ll> ttt(a, a + n);
        std::sort(ttt.begin(), ttt.end());
        ll maxday = c[n - 1] - *ttt.begin();
        ll day = 0;
        for (ll jmp = maxday / 2; jmp > 0; jmp >>= 1) {
            while (day + jmp <= maxday && !pass(day + jmp)) day += jmp;
        }
        printf("%lld\n", day + 1);
    }
}
