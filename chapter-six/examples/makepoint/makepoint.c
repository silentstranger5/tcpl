#include <stdio.h>

#define XMAX 100
#define YMAX 100

struct point {
    int x;
    int y;
};

struct rect {
    struct point pt1;
    struct point pt2;
};

int main(void)
{
    struct rect screen;
    struct point middle;
    struct point makepoint(int, int);

    screen.pt1 = makepoint(0, 0);
    screen.pt2 = makepoint(XMAX, YMAX);
    middle = makepoint((screen.pt1.x + screen.pt2.x) / 2,
		       (screen.pt1.y + screen.pt2.y) / 2);
    return 0;
}

/* makepoint:  make a point from x and y components */
struct point makepoint(int x, int y)
{
    struct point temp;

    temp.x = x;
    temp.y = y;
    return temp;
}

