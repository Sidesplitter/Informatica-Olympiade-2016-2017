

#ifndef INFORMATICA_OLYMPIADE_2016_2017_TESTS_EXPORTER_H
#define INFORMATICA_OLYMPIADE_2016_2017_TESTS_EXPORTER_H


#include <json.hpp>
#include "Path.h"

class Exporter {

    nlohmann::json convertPathToJson(Path path);
    nlohmann::json convertPathsToJson(std::vector<Path> paths);

public:
    void exportPath(Path path, std::string fileName);
    void exportPaths(std::vector<Path> paths, std::string fileName);
};


#endif //INFORMATICA_OLYMPIADE_2016_2017_TESTS_EXPORTER_H
