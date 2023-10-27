struct IntervalContainer {
    using T = int64_t;
    using I = std::array<int64_t, 2>;
    // [l, r)
    std::set<I> data;
    int64_t covered = 0;

    static constexpr T len(I ival) {
        return ival[1] - ival[0];
    }

    void addInterval(T l, T r) {
        if (l >= r) return;
        auto it = data.lower_bound(I{l, r});

        // merge with later intervals
        while (it != data.end() && (*it)[0] <= r) {
            r = std::max(r, (*it)[1]);
            covered -= len(*it);
            it = data.erase(it);
        }

        // merge with prior intervals
        while (it != data.begin()) {
            auto before = std::prev(it);
            if (auto [il, ir] = *before; ir >= l) {
                l = std::min(l, il);
                r = std::max(r, ir);
                covered -= len(*before);
                before = data.erase(before);
            } else {
                break;
            }
        }

        auto [pos, isNew] = data.insert(I{l, r});
        covered += len(*pos);
    }

    int64_t totalCovered() const {
        return covered;
    }
};
