
#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>

typedef long long ll;

struct Foo {
    ll m, s, t;
};

struct Comp {
    bool operator () (const Foo& a, const Foo& b) {
        return a.t < b.t;
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
    // ============ IMPORTANT !!!!!!!!!!!!! ==============
    // Two Foo objects are the same if their member variables t are the same.
    // If we use std::set<Foo>, we will lose Foo objects with the same t values except the first one.
    // So we have to use std::multiset<Foo> !!!
    // ============ IMPORTANT !!!!!!!!!!!!! ==============
    std::multiset<Foo, Comp> s;
    s.insert({0, INT_MIN, INT_MAX});
    for (Foo& x : v) {
        auto it = s.begin();
        while (it->t < x.s) {
            tmp -= it->m;
            it = s.erase(it);
        }
        s.insert(x);
        tmp += x.m;
        if (tmp > ans) ans = tmp;
    }

    printf("%lld\n", ans);
}
