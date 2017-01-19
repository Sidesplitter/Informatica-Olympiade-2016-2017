#include <iostream>
#include "Renderer.h"
#include "../CCore/CCore.h"
#include "CRender.h"

int main(int, char **) {

    CRender *cRender;

    try {
        cRender = new CRender();
    } catch (std::runtime_error exception) {

        std::cerr << exception.what();
        return 1;
    }
    
    cRender->run();

    delete cRender;
    
    return 0;
}