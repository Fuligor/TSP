#include "Result.h"

distance Result::getLength(std::shared_ptr<Graph> graph)
{
    distance result = 0;

    for(int i = 0; i < 2; ++i) {
        auto last = cycle[i].front();

        for(auto j: cycle[i]) {
            result += (*graph.get())[j][last];
            last = j;
        }

        result += (*graph.get())[cycle[i].front()][last];
    }

    return result;
}
