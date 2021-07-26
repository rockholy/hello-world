
// Divide and conquer.

#include <cstdio>
#include <cstring>
#include <vector>

typedef long long ll;

const int N = 1e5;

ll t[N];
ll w[N];
ll zt[N];
ll zw[N];

bool comp (ll a, ll b) {
    return t[a] * w[b] < t[b] * w[a];
}

void go (ll left, ll right) {
    if (left == right) return;

    ll mid = (left + right) / 2;
    go (left, mid);
    go (mid + 1, right);

    ll a = left;
    ll b = mid + 1;
    ll c = 0;
    while (a <= mid && b <= right) {
        if (comp(a, b)) {
            zt[c] = t[a];
            zw[c++] = w[a++];
        }
        else {
            zt[c] = t[b];
            zw[c++] = w[b++];
        }
    }
    while (a <= mid) {
            zt[c] = t[a];
            zw[c++] = w[a++];
    }
    while (b <= right) {
            zt[c] = t[b];
            zw[c++] = w[b++];
    }
  
    memcpy(t + left, zt, (right - left + 1) * sizeof(ll));
    memcpy(w + left, zw, (right - left + 1) * sizeof(ll));
}

int main () {
    ll n;
    scanf("%lld", &n);
    for (ll i = 0; i < n; i++) scanf("%lld", &t[i]);
    for (ll i = 0; i < n; i++) scanf("%lld", &w[i]);

    go(0, n - 1);

    ll ans = 0;
    ll psum = 0;
    for (ll i = 0; i < n; i++) {
        psum += t[i];
        ans += psum * w[i];
    }

    printf("%lld\n", ans);
}
