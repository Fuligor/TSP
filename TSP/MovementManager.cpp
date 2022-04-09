#include "MovementManager.h"

/*int* MovementManager::getClosest(int n, unsigned int node, std::shared_ptr<Graph> graph)
{
	int * result = new int[n];
	for (int i = 0; i < n; i++) result[i] = -1;

	for (int i = 0; i < graph->getSize(); i++)
	{
		if (i != node)
		{

			int mx = 0;
			for (int m = 0; m < n; m++)
			{
				if (result[m] == -1)
				{
					result[m] = i;
					mx = m;
					break;
				}
				else if ((*graph.get())[node][result[mx]] < (*graph.get())[node][result[m]]  )
				{
					mx = m;
				}
			}
			if ((*graph.get())[node][i] < (*graph.get())[node][result[mx]])
			{
				result[mx] = i;
			}
		}
		
	}

	return result;
}*/
