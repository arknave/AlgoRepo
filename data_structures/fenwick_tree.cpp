#include <cstdio>

using namespace std;

const int MAXN = 100005;

// 1 indexing
long long f_tree[MAXN];
// Use the below definition for large ranges
// map<long long, long long> f_tree;

// return a[1] + a[2] + ... + a[x]
long long query(int x) {
    long long ans = 0LL;
    for (int i = x; i > 0; i -= (i & -i)) {
        ans += f_tree[i];
    }

    return ans;
}

// return a[l] + a[l + 1] + a[l + 2] + ... + a[r]
long long query(int l, int r) {
    if (l)
        return query(r) - query(l - 1);
    else
        return query(r);
}

// equivalent to a[x] += v
void update(int x, long long v) {
    for (int i = x; i < MAXN; i += (i & -i)) {
        f_tree[i] += v;
    }
}

int main() {

    return 0;
}
