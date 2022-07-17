#include <cstdio>

using namespace std;

// 0 indexed template
struct BIT {
    using T = int32_t;
    T unit = 0;

    static T f(const T& a, const T& b) {
        return a + b;
    }

    int32_t n;
    std::vector<T> f_tree;
    BIT(int32_t n): n(n) {
        f_tree.assign(n + 1, unit);
    }

    // data[x] = f(data[x], v)
    void update(int32_t x, T v) {
        for (++x; x <= n; x += (x & -x)) {
            f_tree[x] = f(f_tree[x], v);
        }
    }

    // f applied to range [0..x]
    T query(int x) const {
        T res = unit;
        for (++x; x > 0; x -= (x & -x)) {
            res = f(res, f_tree[x]);
        }

        return res;
    }

    /*
    // query [l, r]
    // only valid for invertible functions
    inline T query(int l, int r) const {
        return query(r) - query(l - 1);
    }
    */
};

struct BIToBIT {
    using T = BIT::T;
    int32_t n;
    std::vector<BIT> f_tree;
    std::vector<std::vector<T>> vals;

    BIToBIT(int32_t n): n(n) {
        f_tree.reserve(n + 1);
        vals.resize(n + 1);
    }

    void insert(int32_t idx, int32_t v) {
        for (++idx; idx <= n; idx += (idx & -idx)) {
            vals[idx].push_back(v);
        }
    }

    void finalize() {
        f_tree.emplace_back(0);
        for (int32_t i = 1; i <= n; ++i) {
            std::sort(vals[i].begin(), vals[i].end());
            vals[i].erase(std::unique(vals[i].begin(), vals[i].end()), vals[i].end());
            int32_t m = vals[i].size();
            f_tree.emplace_back(m);
        }
    }

    void update(int32_t idx, int32_t v, T d) {
        for (++idx; idx <= n; idx += (idx & -idx)) {
            auto it = std::lower_bound(vals[idx].begin(), vals[idx].end(), v);
            assert(*it == v);
            f_tree[idx].update(it - vals[idx].begin(), d);
        }
    }

    // get sum of values <= v where idx <= idx
    T query(int32_t idx, int32_t v) {
        T res = f_tree[0].unit;
        for (++idx; idx > 0; idx -= (idx & -idx)) {
            auto it = std::upper_bound(vals[idx].begin(), vals[idx].end(), v);
            T sub = f_tree[idx].query(it - vals[idx].begin() - 1);

            res = BIT::f(res, sub);
        }

        return res;
    }
};

const int MAXN = 100005;

// 1 indexing
ll f_tree[MAXN];
// Use the below definition for large ranges
// map<ll, ll> f_tree;

// return a[1] + a[2] + ... + a[x]
ll query(ll x) {
    ll ans = 0LL;
    for (ll i = x; i > 0; i -= (i & -i)) {
        ans += f_tree[i];
    }

    return ans;
}

// return a[l] + a[l + 1] + a[l + 2] + ... + a[r]
ll query(ll l, ll r) {
    return query(r) - query(l - 1);
}

// equivalent to a[x] += v
void update(ll x, ll v) {
    for (ll i = x; i < MAXN; i += (i & -i)) {
        f_tree[i] += v;
    }
}

int main() {

    return 0;
}
