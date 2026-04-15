#include <iostream>
#include <cmath>

// Inline plotting function for performance
inline void plotPoint(int x, int y) {
    std::cout << "(" << x << ", " << y << ")\n";
}

// Optimized Bresenham Line Algorithm (all octants)
void bresenhamLine(int x1, int y1, int x2, int y2) {

    const int dx = std::abs(x2 - x1);
    const int dy = std::abs(y2 - y1);

    const int sx = (x1 < x2) ? 1 : -1;
    const int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {

        plotPoint(x1, y1);

        if (x1 == x2 && y1 == y2)
            return;

        const int e2 = err << 1;   // faster than 2 * err

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

int main() {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x1, y1, x2, y2;

    std::cout << "Enter x1 y1: ";
    if (!(std::cin >> x1 >> y1)) {
        std::cerr << "Invalid input\n";
        return EXIT_FAILURE;
    }

    std::cout << "Enter x2 y2: ";
    if (!(std::cin >> x2 >> y2)) {
        std::cerr << "Invalid input\n";
        return EXIT_FAILURE;
    }

    std::cout << "Points on the line:\n";

    bresenhamLine(x1, y1, x2, y2);

    return EXIT_SUCCESS;
}
