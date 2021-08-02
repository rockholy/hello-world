
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

typedef long long ll;

struct Foo {
    ll m, s, t;
};

struct Comp {
    bool operator () (const Foo& a, const Foo& b) {
        return a.t > b.t;
    }
};

int main () {
    ll n;
    (void)!scanf("%lld", &n);
    std::vector<Foo> v(n);
    for (Foo& x : v) (void)!scanf("%lld %lld %lld", &x.m, &x.s, &x.t);
    std::sort(v.begin(), v.end(), [](const Foo& a, const Foo& b) { return a.s < b.s; });

    ll ans = 0;
    ll tmp = 0;
    // I want to get the SMALLEST value in the std::priority_queue<Foo>,
    // so Comp is a std::greater<> like class.
    std::priority_queue<Foo, std::vector<Foo>, Comp> pr;
    pr.push({0, INT_MIN, INT_MAX});
    for (Foo& x : v) {
        while (pr.top().t < x.s) {
            tmp -= pr.top().m;
            pr.pop();
        }
        pr.push(x);
        tmp += x.m;
        if (tmp > ans) ans = tmp;
    }

    printf("%lld\n", ans);
}
