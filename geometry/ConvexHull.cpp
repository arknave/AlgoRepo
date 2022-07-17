// Computes the convex hull of a list of points
// Points can be given in any order
// Returned hull has points in counter-clockwise order
// Points on the hull edge are not considered part of the hull, change using STRICT template
// Note that both versions still deduplicate points.
template <bool STRICT=true>
std::vector<P> convexHull(std::vector<P> pts) {
    std::sort(pts.begin(), pts.end());
    pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
    if (pts.size() <= 2) {
        return pts;
    }

    auto check = [](auto val) -> bool {
        if constexpr (STRICT) {
            return val <= 0;
        } else {
            return val < 0;
        }
    };

    std::vector<P> hull;
    hull.reserve(pts.size() + 1);
    for (int32_t iter = 0; iter < 2; ++iter) {
        size_t start = hull.size();
        for (P pt : pts) {
            while (hull.size() >= start + 2 && check(hull[hull.size() - 2].cross(hull.back(), pt))) {
                hull.pop_back();
            }

            hull.push_back(pt);
        }

        hull.pop_back();
        std::reverse(pts.begin(), pts.end());
    }

    return hull;
}
