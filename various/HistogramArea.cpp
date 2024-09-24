// Given a sequence of points (h, w)
// find the largest histogram area
int64_t histogramArea(const std::vector<std::array<int64_t, 2>>& rects) {
    // h, x
    std::vector<std::array<int64_t, 2>> stk;
    stk.push_back({0, 0});
    int64_t ans = 0;
    int64_t x = 0;
    auto process = [&](int64_t h, int64_t w) {
        assert(h >= 0);
        assert(w > 0);
        while (h < stk.back()[0]) {
            auto h2 = stk.back()[0];
            stk.pop_back();
            auto l = stk.back()[1];
            auto r = x;

            ans = std::max(ans, h2 * (r - l));
        }

        x += w;
        stk.push_back({h, x});
    };

    for (auto [h, w] : rects) {
        process(h, w);
    }
    process(0, 0);

    return ans;
}
