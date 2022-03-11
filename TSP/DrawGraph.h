#pragma once
#include <memory>

#include "Result.h"

typedef std::pair <int, int> location;

class DrawGraph
{
public:
	static void showGraph(location* locations, std::shared_ptr <Result>  result);
};

