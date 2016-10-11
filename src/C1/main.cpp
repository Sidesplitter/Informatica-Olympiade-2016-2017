#include <iostream>
#include "../CCore/CCore.h"

int main() {

#ifdef HUMAN_MESSAGES
    std::cout << "==== C1 ====" << std::endl
              << "This program expects a list of 10 numbers and returns 'ja' (yes) or 'nee' (no) depending on whether "
              << "the number is a prime or not." << std::endl;
#endif

    int numbers[10] = {};

    // Capture ten numbers
    for (int i = 0; i < 10; i++) {

#ifdef HUMAN_MESSAGES

        printf("Number %d: ", i + 1);
#endif
        std::cin >> numbers[i];
    }

    CCore cCore = CCore();

    //Check if they are prime
    for(int i = 0; i < 10; i++)
    {

#ifdef HUMAN_MESSAGES
    printf("Number %d (%d): ", i + 1, numbers[i]);
#endif
        if(cCore.isPrime((uint32_t) numbers[i]))
        {
            std::cout << "ja" << std::endl;
        }else{
            std::cout << "nee" << std::endl;
        }
    }
}