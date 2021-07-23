#include <cstdio>
#include <vector>
#include <deque>
#include <algorithm>

typedef long long ll;

struct Point {
	ll x, y;
};

int main () {
	ll n, l;
	(void)!scanf("%lld %lld", &n, &l);
	std::vector<Point> v(n);
	for (ll i = 0; i < n; i++) (void)!scanf("%lld", &v[i].x);
	for (ll i = 0; i < n; i++) (void)!scanf("%lld", &v[i].y);
	std::sort(v.begin(), v.end(), [](const Point& a, const Point& b) { return a.x < b.x; });

	std::deque<Point> maxy, miny;
	ll ans = 0;

	for (ll right = 0; right < n; right++) {
		while (!maxy.empty() && (v[right].x - maxy.front().x) > l) maxy.pop_front();
		while (!miny.empty() && (v[right].x - miny.front().x) > l) miny.pop_front();

		while (!maxy.empty() && maxy.back().y <= v[right].y) maxy.pop_back();
		maxy.push_back(v[right]);

		while (!miny.empty() && miny.back().y >= v[right].y) miny.pop_back();
		miny.push_back(v[right]);

		ll diff = maxy.front().y - miny.front().y;
		if (diff > ans) ans = diff;
	}

	printf("%lld\n", ans);
}
