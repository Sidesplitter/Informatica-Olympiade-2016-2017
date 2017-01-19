#include <iostream>
#include "../CCore/CCore.h"
#include "../CCore/Exporter.h"

int main() {

#ifdef HUMAN_MESSAGES
    std::cout << "==== C3 ====" << std::endl
              << "This program will calculate the largest loop of gaussian points within a given area. "
                      "The calculation time of this program may be quite high, since it cannot perform any square"
                      "optimizations" << std::endl
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

    Path path = cCore.getLargestLoop(std::make_tuple(point1, point2), progress);

#ifdef HUMAN_MESSAGES
   printf("The path starting at (%d, %d) does%s loop, has %lu points, is%s a square and has a length of ",
           path.getStartingPoint().getX(),
           path.getStartingPoint().getY(),
           path.isLoop() ? "" : " not",
           path.getPoints().size(),
           path.isSquare() ? "" : " not"
    );
    
    delete progress;
#endif
    std::cout << path.getLength() << std::endl;

}