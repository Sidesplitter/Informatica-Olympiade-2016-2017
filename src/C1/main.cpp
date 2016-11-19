#include <iostream>
#include "../CCore/CCore.h"

int main() {

#ifdef HUMAN_MESSAGES
    std::cout << "==== C1 ====" << std::endl
              << "This program expects a list of 10 gaussian numbers and returns 'ja' (yes) or 'nee' (no) depending on "
                      "whether the number is a gaussian prime or not. It expects two numbers separated by a space for "
                      "every gaussian number." << std::endl;
#endif

    Point numbers[10] = {};


    // Capture ten numbers
    for (int i = 0; i < 10; i++) {

#ifdef HUMAN_MESSAGES

        printf("Guassian number %d: ", i + 1);
#endif
        int x, y;

        std::cin >> x;
        std::cin >> y;

        numbers[i] = Point(x, y);
    }

    CCore cCore = CCore();

    //Check if they are prime
    for (int i = 0; i < 10; i++) {

#ifdef HUMAN_MESSAGES
        printf("Number %d (%d, %d): ", i + 1, numbers[i].getX(), numbers[i].getY());
#endif
        if (cCore.getPrimalityTester()->isGaussianPrime(numbers[i])) {
            std::cout << "ja" << std::endl;
        } else {
            std::cout << "nee" << std::endl;
        }
    }
}