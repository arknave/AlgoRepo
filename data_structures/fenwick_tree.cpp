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
            f_tree[x] = f_tree[x] + v;
        }
    }

    T query(int x) const {
        T res = unit;
        for (++x; x; x -= (x & -x)) {
            res = res + f_tree[x];
        }

        return res;
    }

    /*
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
ll query(int x) {
    long long ans = 0LL;
    for (int i = x; i > 0; i -= (i & -i)) {
        ans += f_tree[i];
    }

    return ans;
}

// return a[l] + a[l + 1] + a[l + 2] + ... + a[r]
ll query(int l, int r) {
    if (l)
        return query(r) - query(l - 1);
    else
        return query(r);
}

// equivalent to a[x] += v
void update(int x, ll v) {
    for (int i = x; i < MAXN; i += (i & -i)) {
        f_tree[i] += v;
    }
}

int main() {

    return 0;
}
