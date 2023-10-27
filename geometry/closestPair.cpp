// returns the pair of closest points
// currently only works with Point<double>
// TODO: make work with integer points
using P = Point<double>;
std::pair<P, P> closestPair(std::vector<P> points) {
    std::sort(points.begin(), points.end(), [](const P& a, const P& b) { return a.y < b.y; });
    std::set<P> active;
    int32_t n = points.size();

    constexpr double INF = std::numeric_limits<double>::infinity();
    double ans = INF;
    std::pair<P, P> ret = std::pair{P{}, P{}};
    for (int32_t i = 0, j = 0; i < n; ++i) {
        auto sqrtAns = 1.0 + std::sqrt(ans);
        const P& a = points[i];
        while (a.y - points[j].y >= sqrtAns) {
            active.erase(points[j++]);
        }

        for (auto it = active.lower_bound(P{a.x - sqrtAns, a.y});
                  it != active.end() && it->x <= a.x + sqrtAns;
                  ++it) {
            double curDist = (a - *it).dist2();
            if (curDist < ans) {
                ans = curDist;
                ret = {*it, a};
            }
        }

        active.insert(a);
    }

    return ret;
}
