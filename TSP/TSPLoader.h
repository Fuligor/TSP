#pragma once
#include "AbstractLoader.h"

#include <fstream>

typedef std::pair <int, int> location;

class TSPLoader:
    public AbstractLoader
{
    location* locations = nullptr;
    std::ifstream file;

    std::pair <std::string, std::string> getEntry(const std::string& line);
    std::shared_ptr<Graph> loadMetaData();
    void loadLocations();
    void createGraph(std::shared_ptr<Graph>& graph) const;
public:
    ~TSPLoader();

    // Odziedziczono za pośrednictwem elementu AbstractLoader
    virtual std::shared_ptr<Graph> loadFile(std::string fileName) override;
    location* getLocation();
};

