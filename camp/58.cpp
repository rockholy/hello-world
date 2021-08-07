
#include <cstdio>
#include <vector>

typedef long long ll;

ll n, m;

// Every v[i] could do the operation [0, count] times.
bool pass (const std::vector<ll>& v, ll count) {
    ll tmpmax = 0;
    for (ll i = 0; i < n; i++) {
        if (v[i] + count < m) {
            // The range could be [v[i], v[i] + count].
            if (v[i] + count >= tmpmax) {
                if (v[i] > tmpmax) tmpmax = v[i];
            }
            else return false;
        }
        else {
            // The range could be one of the followings:
            // 1. [v[i], m - 1] 
            // 2. [0, v[i] + count - m]
            // We prefer to keep tmpmax small, so check condition 2 first.
            // Condition 2 is also the only chance that when v[i] > tmpmax,
            // tmpmax may not need to be set to v[i].
            if (v[i] + count - m >= tmpmax) continue;
            // Check condition 1. Note that m - 1 must be >= tmpmax.
            if (v[i] > tmpmax) tmpmax = v[i];
        }
    }
    return true;
}

int main () {
    (void)!scanf("%lld %lld", &n, &m);
    std::vector<ll> v(n);
    for (ll i = 0; i < n; i++) (void)!scanf("%lld", &v[i]);

    bool ok = true;
    for (ll i = 1; i < n; i++) {
        if (v[i] < v[i - 1]) {
            ok = false;
            break;
        }
    }
    if (ok) printf("0\n");
    else {
        ll ans = 0;
        for (ll jmp = m / 2; jmp > 0; jmp >>= 1) {
            while (ans + jmp <= m && !pass(v, ans + jmp)) ans += jmp;
        }
        printf("%lld\n", ans + 1);
    }
}
