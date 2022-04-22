#pragma once
#include "SteepLocalSearch.h"
class MSLS :
    public SteepLocalSearch
{
public:
    template <typename... Args>
    MSLS(std::shared_ptr <AbstractAlgorithm> baseAlgorithm, Args... args);
    virtual std::string getName() override;
    virtual void calculate(int startingNode) override;
};
template<typename ...Args>
inline MSLS::MSLS(std::shared_ptr<AbstractAlgorithm> baseAlgorithm, Args ...args) :
    SteepLocalSearch(baseAlgorithm, args...)
{
}
