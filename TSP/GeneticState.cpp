#include "GeneticState.h"

GeneticState::GeneticState(std::shared_ptr<Result> result)
    :Result(*result)
{
    for(int i = 0; i < 2; ++i)
    {
        int last = -1;

        for(auto j: result->cycle[i])
        {
            if(last != -1)
            {
                _edges[last] = j;
            }

            last = j;
        }

        _edges[last] = result->cycle[i].front();
    }
}

std::shared_ptr <Result> GeneticState::crossover(const std::shared_ptr <GeneticState>& a, const std::shared_ptr <GeneticState>& b)
{
    auto result = std::make_shared <Result>();

    for (int i = 0; i < 2; ++i)
    {
        int last = -1;
        auto iterator = result->cycle[i].before_begin();

        for (auto j : a->cycle[i])
        {
            if (last != -1)
            {
                if (b->containEdge(j, last))
                {
                    iterator = result->cycle[i].insert_after(iterator, j);
                }
            }

            last = j;
        }

        if (b->containEdge(a->cycle[i].front(), last))
        {
            iterator = result->cycle[i].insert_after(iterator, a->cycle[i].front());
        }
    }

    return result;
}

distance GeneticState::getLength(std::shared_ptr<Graph> graph)
{
    if (_distance == -1)
    {
       _distance = Result::getLength(graph);
    }

    return _distance;
}

bool GeneticState::containEdge(int a, int b) const
{
    return _edges.at(a) == b || _edges.at(b) == a;
}

void GeneticState::insert(int a, int b, int iCycle, std::forward_list <int>::iterator& iterator)
{
    iterator = cycle[iCycle].insert_after(iterator, a);
    _edges[b] = a;
}
