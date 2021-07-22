#include <cstdio>
#include <vector>

typedef long long ll;

int main () {
	ll n;
	scanf("%lld", &n);
	std::vector<ll> v(n);
	for (ll i = 0; i < n; i++) scanf("%lld", &v[i]);

	std::vector<ll> index(n, -1);

	ll left = 0;
	ll count = 0;
	ll ans = 0;
	for (ll right = 0; right < n; right++) {
		ll color = v[right];
		if (index[color] == -1) {
			index[color] = right;
			count++;
			if (count > ans) ans = count;
		}
		else {
			ll tmp = index[color];
			for (ll i = left; i <= tmp; i++) index[v[i]] = -1;
			left = tmp + 1;
			count = right - left + 1;
			index[color] = right;
		}
	}
	printf("%lld\n", ans);
}
