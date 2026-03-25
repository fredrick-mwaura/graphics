#include <stdio.h>
#include <stdlib.h>

// Function to plot a point (for demonstration, we just print coordinates)
void plotPoint(int x, int y) {
    printf("(%d, %d)\n", x, y);
}

// Bresenham's Line Drawing Algorithm
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1; // Step direction for x
    int sy = (y1 < y2) ? 1 : -1; // Step direction for y
    int err = dx - dy;           // Error term

    while (1) {
        plotPoint(x1, y1); // Plot the current point

        if (x1 == x2 && y1 == y2) break; // End condition

        int e2 = 2 * err;
        if (e2 > -dy) { // Move in x direction
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) { // Move in y direction
            err += dx;
            y1 += sy;
        }
    }
}

int main() {
    int x1, y1, x2, y2;

    printf("Enter x1 y1: ");
    if (scanf("%d %d", &x1, &y1) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter x2 y2: ");
    if (scanf("%d %d", &x2, &y2) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Points on the line:\n");
    bresenhamLine(x1, y1, x2, y2);

    return 0;
}
