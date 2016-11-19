#include <iostream>
#include "../CCore/CCore.h"

int main() {

#ifdef HUMAN_MESSAGES
    std::cout << "==== C4 ====" << std::endl
              << "This program will calculate the largest path of gaussian points within a given area "
              << "that is a square. The final answer is the x + y of the bottom left of the largest square" << std::endl
              << "Please enter the search area (x1 x2 y1 y2): ";
#endif

    int x1, x2, y1, y2;
    std::cin >> x1 >> x2 >> y1 >> y2;

    Point point1 = Point(x1, y1);
    Point point2 = Point(x2, y2);

    CCore cCore = CCore();

    Progress *progress = nullptr;
#ifdef HUMAN_MESSAGES
    progress = new Progress();
#endif

    Path square = cCore.getLargestSquare(std::make_tuple(point1, point2), progress);

#ifdef HUMAN_MESSAGES
    printf("\nThe largest square was found at (%d, %d) with sides of %d long and a total length of %d. "
                   "This means that the final answer is: ",
           square.getStartingPoint().getX(),
           square.getStartingPoint().getY(),
           square.getLength() / 4,
           square.getLength());
#endif
    std::cout << square.getStartingPoint().getX() + square.getStartingPoint().getY() << std::endl;

}