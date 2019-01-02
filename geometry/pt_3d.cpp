#include <cstdio>
#include <cmath>
#include <vector>

// https://open.kattis.com/problems/threedprinter

using namespace std;

struct pt {
    long double x, y, z;

    pt operator+(const pt& b) const {
        return {x + b.x, y + b.y, z + b.z};
    }

    pt operator-(const pt& b) const {
        return {x - b.x, y - b.y, z - b.z};
    }

    pt operator/(const long double v) const {
        return {x / v, y / v, z / v};
    }

    pt operator*(const long double v) const {
        return {v * x, v * y, v * z};
    }

    long double operator*(const pt& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    pt operator^(const pt& other) const {
        return {y * other.z - z * other.y, - x * other.z + z * other.x, x * other.y - y * other.x};
    }

    long double norm() const {
        return sqrt(x * x + y * y + z * z);
    }
};

pt operator*(const long double& k, const pt& p) {
    return p * k;
}

// Gets the area of a set of points
long double get_area(const vector<pt>& points) {
    // Shoelace theorem. Cross all the consecutive edges
    // At the end, dot with normal to plane
    pt normal = (points[1] - points[0]) ^ (points[2] - points[0]);
    normal = normal / normal.norm();

    pt crozz = {0, 0, 0};
    for (int i = 0; i < points.size() - 1; ++i) {
        crozz = crozz + (points[i] ^ points[i + 1]);
    }

    crozz = crozz + (points.back() ^ points[0]);

    return normal * crozz / 2.0;
}

// Get the normal vector to a plane. Assumes the vector has at least three points
pt get_normal(const vector<pt>& points) {
    pt norm = (points[1] - points[0]) ^ (points[2] - points[0]);
    long double mag = norm.norm();

    return norm / mag;
}

// Use the projection matrix harry
long double get_dist(const pt& norm, const pt& query) {
    // Say the norm is [a b c]
    // Then the projection matrix is 
    // aa ab ac
    // ab bb bc
    // ac bc cc

    // mutliply that by query to get a vector, return its norm
    
    // This math works out to the matrix multiplication above.
    pt proj = (norm * query) * norm;

    return proj.norm();
}

// Gets the volume of a series of points. It breaks the region up
// into triangular pyramids and calculates the volume of each pyramid.
long double volume() {
    // Number of faces
    int f;
    scanf("%d", &f);

    long double vol = 0.0L;

    int v;
    long double x, y, z;
    long double cx = 0.0L, cy = 0.0L, cz = 0.0L;
    int total_vert = 0;

    vector<long double> areas;
    vector<pt> normals;
    vector<pt> anchor;

    for (int i = 0; i < f; ++i) {
        scanf("%d", &v);
        total_vert += v;

        vector<pt> points;
        for (int j = 0; j < v; ++j) {
            scanf("%Lf %Lf %Lf", &x, &y, &z);
            points.push_back({x, y, z});

            cx += x;
            cy += y;
            cz += z;
        }

        areas.push_back(get_area(points));
        normals.push_back(get_normal(points));
        anchor.push_back(points[0]);
    }

    cx /= total_vert;
    cy /= total_vert;
    cz /= total_vert;

    pt center = {cx, cy, cz};

    for (int i = 0; i < f; ++i) {
        // volume of a pyramid is 1/3 B h
        vol += areas[i] * get_dist(normals[i], center - anchor[i]) / 3.0L;
    }

    return vol;
}

int main() {
    int n;
    scanf("%d", &n);

    long double ans = 0.0L;
    for (int i = 0; i < n; ++i) {
        ans += volume();
    }

    printf("%.2Lf\n", ans);
    return 0;
}
