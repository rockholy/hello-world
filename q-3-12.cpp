#include <cstdio>
#include <vector>
#include <map>

typedef long long ll;

int main () {
	ll m, n;
	scanf("%lld %lld", &m, &n);
	std::vector<ll> v(n);
	std::map<ll, ll> table;
	for (ll i = 0; i < n; i++) {
		scanf("%lld", &v[i]);
		table.insert({v[i], 0});
	}

	ll pos = 0;
	for (auto& x : table) x.second = pos++;

	for (ll i = 0; i < n; i++) v[i] = table[v[i]];

	std::vector<ll> index(n, -1);

	ll left = 0;
	ll count = 0;
	ll ans = 0;
	for (ll right = 0; right < n; right++) {
		ll color = v[right];
		if (index[color] == -1) {
			index[color] = right;
			count++;
			if (count == m) ans++;
		}
		else {
			ll tmp = index[color];
			for (ll i = left; i <= tmp; i++) index[v[i]] = -1;
			left = tmp + 1;
			count = right - left + 1;
			if (count == m) ans++;
			index[color] = right;
		}
	}
	printf("%lld\n", ans);
}
