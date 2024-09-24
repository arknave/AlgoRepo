template <typename T>
struct Point {
    T x;
    T y;

    Point(T x={}, T y={}): x(x), y(y) {}

    using P = Point;

    bool operator==(P o) const {
        return (x == o.x) & (y == o.y);
    }

    auto operator<=>(P o) const = default;

    /*
    // for pre c++20...
    bool operator<(P o) const {
        return std::tie(x, y) < std::tie(o.x, o.y);
    }
    */

    P& operator+=(P other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    P operator+(P other) const {
        return P{*this} += other;
    }

    P& operator-=(P other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    P operator-(P other) const {
        return P{*this} -= other;
    }

    T dot(P other) const {
        return x * other.x + y * other.y;
    }

    T cross(P other) const {
        return x * other.y - y * other.x;
    }

    // Computes the cross product of a and b relative to this.
    T cross(P a, P b) const {
        return (a - *this).cross(b - *this);
    }

    double dist() const {
        return std::sqrt(static_cast<double>(dist2()));
    }

    T dist2() const {
        return dot(*this);
    }

    friend std::istream& operator>>(std::istream& is, P& pt) {
        return is >> pt.x >> pt.y;
    }

    friend std::ostream& operator<<(std::ostream& os, const P& pt) {
        return os << "(" << pt.x << ", " << pt.y << ")";
    }
};

template <typename T>
Point<T> operator*(T scale, Point<T> p) {
    return p * scale;
}
