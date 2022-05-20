#pragma once
#include "SteepLocalSearch.h"
class GeneticAlgorithm:
    public SteepLocalSearch
{
protected:
    double _workTime;
    int _version;
public:
    template <typename... Args>
    GeneticAlgorithm(int version, double workTime, std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);
    // Odziedziczono za poœrednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;
    virtual void calculate(int startingNode) override;
};

template<typename ...Args>
inline GeneticAlgorithm::GeneticAlgorithm(int version, double workTime, std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args)
    :SteepLocalSearch(baseAlgorithm, args...), _workTime(workTime), _version(version)
{
}
