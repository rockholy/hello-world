
#include <cstdio>
#include <vector>

typedef long long ll;

const int maxn = 28;
ll v[maxn][maxn];

ll n;
std::vector<ll> a, b;

ll ans = 0;

void go (ll x) {
    if ((ll)a.size() == n && (ll)b.size() == n) {
        ll total = 0;
        for (ll m : a) {
            for (ll n : b) {
                total += v[m][n];
            }
        }
        if (total > ans) ans = total;
        return;
    }
    
    // Put x in team a.
    if ((ll)a.size() < n) {
        a.push_back(x);
        go(x + 1);
        a.pop_back();
    }

    // Put x in team b.
    if ((ll)b.size() < n) {
        b.push_back(x);
        go(x + 1);
        b.pop_back();
    }
}

int main () {
    (void)!scanf("%lld", &n);
    for (ll i = 0; i < 2 * n; i++) {
        for (ll j = 0; j < 2 * n; j++) {
            (void)!scanf("%lld", &v[i][j]);
        }
    }

    go(0);

    printf("%lld\n", ans);
}
