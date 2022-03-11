#include "TSPLoader.h"

#include <map>
#include <string>

#include "Graph.h"

distance square(distance a)
{
	return a * a;
}

distance getDistance(location a, location b)
{
	return sqrt(square(a.first - b.first) + square(a.second - b.second)) + 0.5;
}

std::pair<std::string, std::string> TSPLoader::getEntry(const std::string& line)
{
	unsigned int index = line.find(":");

	std::pair <std::string, std::string> entry;

	entry.first = line.substr(0, index);
	entry.second = line.substr(index + 1);

	for (unsigned int i = 0; i < entry.first.size(); ++i)
	{
		entry.first[i] = tolower(entry.first[i]);
	}

	while (true)
	{
		if (entry.second[0] == ' ')
		{
			entry.second = entry.second.substr(1);
		}
		else
		{
			break;
		}
	}

	return entry;
}

std::shared_ptr<Graph> TSPLoader::loadMetaData()
{
	std::map <std::string, std::string> metadata;

	std::string buf;

	while (true)
	{
		std::getline(file, buf);

		if (buf == "NODE_COORD_SECTION")
		{
			break;
		}

		metadata.insert(getEntry(buf));
	}

	unsigned int size = std::stoul(metadata["dimension"]);

	std::shared_ptr<Graph> graph = std::make_shared <Graph>(size);

	graph->setName(metadata["name"]);

	return graph;
}

void TSPLoader::loadLocations(location* locations)
{
	std::string buf;

	while (true)
	{
		file >> buf;

		if (buf == "EOF")
		{
			break;
		}

		int index = std::stoi(buf) - 1;

		file >> buf;

		int x = std::stoi(buf);

		file >> buf;

		int y = std::stoi(buf);

		location temp(x, y);

		locations[index] = temp;
	}
}

void TSPLoader::createGraph(std::shared_ptr<Graph>& graph, location* locations) const
{
	for (unsigned int i = 0; i < graph->getSize(); ++i)
	{
		for (unsigned int j = i; j < graph->getSize(); ++j)
		{
			if (i == j)
			{
				(*graph.get())[i][j] = 0;
			}

			distance dist = getDistance(locations[i], locations[j]);

			(*graph.get())[i][j] = dist;
			(*graph.get())[j][i] = dist;
		}
	}
}

TSPLoader::~TSPLoader()
{
	if(locations != nullptr)
	{
		delete[] locations;
	}
}

std::shared_ptr<Graph> TSPLoader::loadFile(std::string fileName)
{
	file.open(fileName);

	std::shared_ptr<Graph> graph = loadMetaData();
	if(locations != nullptr)
	{
		delete[] locations;
	}

	location* locations = new location[graph->getSize()];
	loadLocations(locations);
	createGraph(graph, locations);

	file.close();

	return graph;
}

location* TSPLoader::getLocation()
{
	return locations;
}
