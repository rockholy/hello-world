
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>

typedef long long ll;

const int maxn = 1000 + 10;
ll d[maxn];
ll s[maxn];

ll n, t;

bool pass (double v) {
    double totalTime = 0;
    for (ll i = 0; i < n; i++) {
        totalTime += (double)d[i] / (s[i] + v);
    }
    return totalTime <= t;
}

int main () {
    (void)!scanf("%lld %lld", &n, &t);
    for (ll i = 0; i < n; i++) (void)!scanf("%lld %lld", d + i, s + i);

    // s + v > 0 => v > -s.
    ll smin = *std::min_element(s, s + n);
    double vmin = -smin;

    double dsum = std::accumulate(d, d + n, 0);
    double vavg = dsum / t;
    double vmax = vavg - smin;

    double ans = vmin;
    double jmp = (vmax - vmin) / 2;
    for (; jmp >= 1e-10; jmp /= 2) {
        while (ans + jmp <= vmax && !pass(ans + jmp)) ans += jmp;
    }

    // The sum of the number of digits before and after . is 20.
    std::cout << std::setprecision(20) << ans << '\n';
}
