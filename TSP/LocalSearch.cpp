#include "LocalSearch.h"

void LocalSearch::construct(std::shared_ptr<MovementManager> movement)
{
	movementManagers.push_back(movement);
}
