// In-place coordinate compress a vector and return the sorted unique list of values
template <typename T>
std::vector<T> compress(std::vector<T>& a) {
    std::vector<T> vals = a;
    std::ranges::sort(vals);
    vals.erase(std::unique(vals.begin(), vals.end()), vals.end());

    for (auto& x : a) {
        x = std::ranges::lower_bound(vals, x) - vals.begin();
    }

    return vals;
}
