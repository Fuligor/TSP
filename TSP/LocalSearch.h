#pragma once
#include "AbstractAlgorithm.h"

#include <list>
#include <memory>

#include "MovementManager.h"

class LocalSearch:
	public AbstractAlgorithm
{
protected:
	std::list <std::shared_ptr <MovementManager>> movementManagers;
public:
	template <typename... Args>
	LocalSearch(Args... args);
private:
	void construct(std::shared_ptr <MovementManager> movement);
	template <typename... Args>
	void construct(std::shared_ptr <MovementManager> movement, Args... args);
};

template<typename ...Args>
inline LocalSearch::LocalSearch(Args ...args)
{
	construct(args);
}

template<typename ...Args>
inline void LocalSearch::construct(std::shared_ptr<MovementManager> movement, Args ...args)
{
	construct(movement);
	construct(args...);
}
