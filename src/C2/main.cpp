#include <iostream>
#include "../CCore/Point.h"
#include "../CCore/Path.h"

int main() {

#ifdef HUMAN_MESSAGES
    std::cout << "==== C2 ====" << std::endl
              << "This program will calculate the length of the path that starts on the given coordinates in the given "
              << "search area." << std::endl
              << "Please enter the search area (x1 x2 y1 y2): ";
#endif

    int x1, x2, y1, y2;
    std::cin >> x1 >> x2 >> y1 >> y2;

    Point point1 = Point(x1, y1);
    Point point2 = Point(x2, y2);

    int x, y;

#ifdef HUMAN_MESSAGES
    std::cout << "Please enter the starting coordinates of the path (x y): ";
#endif

    std::cin >> x >> y;

    Point startingPoint = Point(x, y);

    Path path = Path(startingPoint, PrimalityTester());

    path.calculatePath(std::make_tuple(point1, point2));

#ifdef HUMAN_MESSAGES

    printf("The path starting at (%d, %d) does%s loop, is%s a square and has a length of ",
           x,
           y,
           path.isLoop() ? "" : " not",
           path.isSquare() ? "" : " not"
    );
#endif
    std::cout << path.getLength();

}