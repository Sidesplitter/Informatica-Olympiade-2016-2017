#include <iostream>
#include "../CCore/Point.h"
#include "../CCore/Path.h"
#include "../CCore/Exporter.h"

int main() {

#ifdef HUMAN_MESSAGES
    std::cout << "==== CExport ====" << std::endl
              << "This program will calculate the length of the path that starts on the given coordinates in the given "
              << "search area. It will output this path to the given file" << std::endl
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

    std::string filePath;
#ifdef HUMAN_MESSAGES
    std::cout << "Please enter the file path to export to: ";
#endif
    std::cin >> filePath;

    //Do the calculations
    Point startingPoint = Point(x, y);

    Path path = Path(startingPoint, new PrimalityTester());

    path.calculatePath(std::make_tuple(point1, point2));

    Exporter exporter;

    exporter.exportPath(path, filePath);
#ifdef HUMAN_MESSAGES

    printf("The path starting at (%d, %d) does%s loop, has %lu points, is%s a square and has a length of %i.\n",
           x,
           y,
           path.isLoop() ? "" : " not",
           path.getPoints().size(),
           path.isSquare() ? "" : " not",
           path.getLength()
    );

    printf("Path is exported to %s.\n", filePath.c_str());
#endif
}