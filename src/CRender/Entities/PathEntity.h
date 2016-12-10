#ifndef PROJECT_PATHENTITY_H
#define PROJECT_PATHENTITY_H

#include "../../CCore/Path.h"
#include "Entity.h"

class PathEntity : public Entity{

private:
    Path path;

public:
    PathEntity(CRender *cRender, const Path &path);

    const Path &getPath() const;

    void setPath(const Path &path);

    void update() override;

    void render() override;
};


#endif //PROJECT_PATHENTITY_H
