#include <cstdio>

using namespace std;

// 0 indexed template
struct BIT {
    using T = ll;
    T unit = 0;

    T f(const T& a, const T& b) const {
        return a + b;
    }

    int n;
    vector<T> f_tree;
    BIT(int n): n(n) {
        f_tree.assign(n + 1, unit);
    }

    void update(int x, T v) {
        for (++x; x <= n; x += (x & -x)) {
            f_tree[x] = f(f_tree[x], v);
        }
    }

    T query(int x) const {
        T res = unit;
        for (++x; x > 0; x -= (x & -x)) {
            res = f(res, f_tree[x]);
        }

        return res;
    }

    /*
    // query [l, r]
    inline T query(int l, int r) const {
        return query(r) - query(l - 1);
    }
    */
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

struct BIT {
    using T = int;
    T unit = 0;

    T f(const T& a, const T& b) const {
        return a + b;
    }

    int n;
    vector<T> f_tree;
    BIT(int n): n(n) {
        f_tree.assign(n + 1, unit);
    }

    void update(int x, T v) {
        for (++x; x <= n; x += (x & -x)) {
            f_tree[x] = f(f_tree[x], v);
        }
    }

    T query(int x) const {
        T res = unit;
        for (++x; x; x -= (x & -x)) {
            res = f(res, f_tree[x]);
        }

        return res;
    }
};

struct BIToBIT {
    int n;
    vector<BIT> f_tree;
    vector<vi> vals;

    BIToBIT(int n): n(n) {
        f_tree.reserve(n + 1);
        vals.resize(n + 1);
    }

    void insert(int idx, int v) {
        for (++idx; idx <= n; idx += (idx & -idx)) {
            vals[idx].push_back(v);
        }
    }

    void finalize() {
        f_tree.emplace_back(0);
        for (int i = 1; i <= n; ++i) {
            sort(all(vals[i]));
            vals[i].erase(unique(all(vals[i])), end(vals[i]));
            int m = vals[i].size();
            f_tree.emplace_back(m);
        }
    }

    void update(int idx, int v, int d) {
        for (++idx; idx <= n; idx += (idx & -idx)) {
            auto it = lower_bound(all(vals[idx]), v);
            assert(*it == v);
            f_tree[idx].update(it - begin(vals[idx]), d);
        }
    }

    // get sum of values <= v where idx <= idx
    int query(int idx, int v) {
        int res = 0;
        for (++idx; idx > 0; idx -= (idx & -idx)) {
            auto it = upper_bound(all(vals[idx]), v);
            res += f_tree[idx].query(it - begin(vals[idx]) - 1);
        }

        return res;
    }
};
