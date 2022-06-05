#pragma once
#include "AbstractAlgorithm.h"
class RandomCycle:
    public AbstractAlgorithm
{
public:
    // Odziedziczono za po�rednictwem elementu AbstractAlgorithm
    virtual std::string getName() override;

protected:
    // Odziedziczono za po�rednictwem elementu AbstractAlgorithm
    virtual void calculate(int startingNode) override;
};

