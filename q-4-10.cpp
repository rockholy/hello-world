
#include <cstdio>
#include <vector>

typedef long long ll;

ll n, m;
std::vector<ll> v;

bool enough (ll f) {
    ll now = f;
    ll count = 0;
    for (ll i = 0; i < n; i++) {
        // If f may be less than v[i], this check is very important !!!
        // No matter how large m is, it's impossible for f to beat v[i] if f < v[i] !!!
        if (f < v[i]) return false;

        if (now >= v[i]) {
            now -= v[i];
            continue;
        }
        count++;
        if (count > m) return false;
        now = f - v[i];
    }
    return true;
}

int main () {
    (void)!scanf("%lld %lld", &n, &m);
    v = std::vector<ll>(n);
    ll total = 0;
    ll pmax = 0;
    for (ll i = 0; i < n; i++) {
        (void)!scanf("%lld", &v[i]);
        if (v[i] > pmax) pmax = v[i];
        total += v[i];
    }
  
    // To support the case where pmax is the final solution, we have to set the initial value of f
    // to be pmax - 1 because at last we will printf(f + 1).
    // Or we could just set f to be 0 here. But if we do so, we must check if f < v[i] in enough().
    // If we set f to be 0 and diff to be total here, we don't need pmax anymore.
    ll f = pmax - 1;
    ll diff = total - pmax;
//  ll f = 0;
//  ll diff = total;
    for (ll jmp = diff / 2; jmp > 0; jmp >>= 1) {
        while (f + jmp <= total && !enough(f + jmp)) f += jmp;
    }

    printf("%lld\n", f + 1);
}
