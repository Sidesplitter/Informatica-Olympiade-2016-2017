#include <fstream>
#include <iostream>
#include "Exporter.h"

nlohmann::json Exporter::convertPathToJson(Path path) {
    nlohmann::json json;

    json["length"] = path.getLength();
    json["sideLength"] = path.getSideLength();
    json["isSquare"] = path.isSquare();
    json["isLoop"] = path.isLoop();
    json["points"] = nlohmann::json::array();

    for(int i = 0; i < path.getPoints().size(); i++)
    {

        Point point = path.getPoints()[i];

        nlohmann::json jsonPoint = nlohmann::json::array();

        jsonPoint.push_back(point.getX());
        jsonPoint.push_back(point.getY());

        json["points"].push_back(jsonPoint);
    }

    return json;
}

nlohmann::json Exporter::convertPathsToJson(std::vector<Path> paths) {
    nlohmann::json json = nlohmann::json::array();

    for(int i = 0; i < paths.size(); i++)
    {
        Path path = paths[i];

        json.push_back(this->convertPathToJson(path));
    }

    return json;
}


void Exporter::exportPath(Path path, std::string fileName) {

    this->exportPaths({path}, fileName);
}

void Exporter::exportPaths(std::vector<Path> paths, std::string fileName) {

    nlohmann::json json = this->convertPathsToJson(paths);

    std::ofstream file (fileName);

    if(!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }

    file << json.dump(4);
    file.close();
}

