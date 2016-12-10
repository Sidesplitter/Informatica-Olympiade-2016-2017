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


    //TODO REMOVE THIS
    /*CCore cCore;
    auto points = cCore.getGaussianPrimes(std::make_tuple(Point(300, 300), Point(400, 400)));

    cRender->getRenderer()->getRenderables().push_back(
            new RenderablePoint(0, 0)
    );

    for (int i = 0; i < points.size(); i++) {

        cRender->getRenderer()->getRenderables().push_back(new RenderablePoint(points[i]));
    }

    auto path = new RenderablePath(Point(174, 89), cCore.getPrimalityTester());
    path->calculatePath(std::make_tuple(Point(0, 0), Point(1000, 1000)));

    cRender->getRenderer()->getRenderables().push_back((Renderable *&&) path);*/

    cRender->run();

    delete cRender;
    
    return 0;
}