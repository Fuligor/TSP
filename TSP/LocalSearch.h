#pragma once
#include "AbstractAlgorithm.h"

#include <list>
#include <memory>

#include "MovementManager.h"

#include <memory>

class LocalSearch:
	public AbstractAlgorithm
{
protected:
	std::shared_ptr <AbstractAlgorithm> _baseAlgorithm;
	std::list <std::shared_ptr <MovementManager>> _movementManagers;
	std::vector <std::shared_ptr <Move>> _moves;
public:
	template <typename... Args>
	LocalSearch(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);

	virtual void setGraph(std::shared_ptr <Graph> graph) override;
	virtual std::string getName() override;
	virtual void calculate(int startingNode) override;
protected:
	virtual bool stopCondition(std::shared_ptr <Move>& move);
	virtual std::shared_ptr <Move>& selectMove() = 0;
private:
	void construct(std::shared_ptr <MovementManager> movement);
	template <typename... Args>
	void construct(std::shared_ptr <MovementManager> movement, Args... args);
};

template<typename ...Args>
inline LocalSearch::LocalSearch(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args ...args):
	_baseAlgorithm(baseAlgorithm)
{
	construct(args...);
}

template<typename ...Args>
inline void LocalSearch::construct(std::shared_ptr<MovementManager> movement, Args ...args)
{
	construct(movement);
	construct(args...);
}
