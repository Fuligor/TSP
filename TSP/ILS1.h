#pragma once
#include "SteepLocalSearch.h"
#include <random>

class ILS1 :
    public SteepLocalSearch
{
private:
    std::mt19937_64 _gen;
    double _workTime;
    std::shared_ptr<Move>& selectRandomMove();
public:
    
    template <typename... Args>
    ILS1(double workTime, std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);
    virtual std::string getName() override;
    virtual void calculate(int startingNode) override;
};

template<typename ...Args>
inline ILS1::ILS1(double workTime, std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args) :
    SteepLocalSearch(baseAlgorithm, args...), _workTime(workTime)
{
}
