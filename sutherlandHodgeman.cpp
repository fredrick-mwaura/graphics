#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

// The axis-aligned clip window
struct ClipRect {
    double xmin, ymin, xmax, ymax;
};

// Compute intersection of segment (P1→P2) with a clip edge defined by a boundary value and an axis ('x' or 'y') and side.
Point intersect(Point s, Point p, char axis, double boundary) {
    Point i;
    if (axis == 'x') {
        i.x = boundary;
        // lerp: how far along S→P does x == boundary?
        double t = (boundary - s.x) / (p.x - s.x);
        i.y = s.y + t * (p.y - s.y);
    } else { // 'y'
        i.y = boundary;
        double t = (boundary - s.y) / (p.y - s.y);
        i.x = s.x + t * (p.x - s.x);
    }
    return i;
}

// "Inside" tests for each of the 4 clip edges
bool insideLeft  (Point p, ClipRect r) { return p.x >= r.xmin; }
bool insideRight (Point p, ClipRect r) { return p.x <= r.xmax; }
bool insideBottom(Point p, ClipRect r) { return p.y >= r.ymin; }
bool insideTop   (Point p, ClipRect r) { return p.y <= r.ymax; }

// Clip a polygon against ONE edge.
// This is the heart of Sutherland-Hodgman.
//
//   input  – polygon to clip
//   inside – function that tests if a point is
//             on the "inside" of this edge
//   axis   – 'x' or 'y' (for intersection math)
//   bound  – the boundary coordinate value
//   rect   – the full clip rectangle
//
// Returns the clipped polygon.
std::vector<Point> clipAgainstEdge(
    const std::vector<Point>& input,
    bool (*inside)(Point, ClipRect),
    char axis,
    double boundary,
    ClipRect rect)
{
    std::vector<Point> output;

    if (input.empty()) return output;

    int n = input.size();
    for (int i = 0; i < n; i++) {
        Point S = input[i];             // previous vertex
        Point P = input[(i + 1) % n];  // current vertex

        bool sInside = inside(S, rect);
        bool pInside = inside(P, rect);

        // Case 1: both inside → emit P
        if (sInside && pInside) {
            output.push_back(P); //add P to end of output
        }
        // Case 2: S inside, P outside → emit intersection
        else if (sInside && !pInside) {
            output.push_back(intersect(S, P, axis, boundary)); //add intersection to end of output
        }
        // Case 3: S outside, P inside → emit I then P
        else if (!sInside && pInside) {
            output.push_back(intersect(S, P, axis, boundary)); //add intersection to end of output
            output.push_back(P);
        }
    }

    return output;
}

// Full Sutherland-Hodgman Polygon Clipping
//
// Clips `polygon` against each of the 4 edges
// of `rect`, feeding the output of one clip
// step as input to the next.
std::vector<Point> sutherlandHodgman(
    std::vector<Point> polygon,
    ClipRect rect)
{
    // Clip against each edge in turn.
    // Order doesn't matter for correctness, but
    // left→right→bottom→top is conventional.
    polygon = clipAgainstEdge(polygon, insideLeft,   'x', rect.xmin, rect);
    polygon = clipAgainstEdge(polygon, insideRight,  'x', rect.xmax, rect);
    polygon = clipAgainstEdge(polygon, insideBottom, 'y', rect.ymin, rect);
    polygon = clipAgainstEdge(polygon, insideTop,    'y', rect.ymax, rect);
    return polygon;
}

// Demo
int main() {
    // A pentagon that partially overlaps the clip window
    std::vector<Point> polygon = {
        {0.5, 1.5},
        {2.5, 0.5},
        {3.5, 2.5},
        {2.0, 4.0},
        {0.0, 3.0}
    };

    // The rectangular clip window
    ClipRect rect = {1.0, 1.0, 3.0, 3.0};

    auto result = sutherlandHodgman(polygon, rect);

    std::cout << "Clipped polygon (" << result.size() << " vertices):\n";
    for (auto& p : result) {
        std::cout << "  (" << p.x << ", " << p.y << ")\n";
    }
    return 0;
}
