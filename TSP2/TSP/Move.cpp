#include "Move.h"

#include "SearchState.h"

#include <iostream>

Move::Move(int node1, int node2, int node3, int node4, int node5, int node6)
	: node { node1, node2, node3, node4, node5, node6 }, type(Move::Type::OUTER)
{
}

Move::Move(int node1, int node2, int node3, int node4)
	:node { node1, node2, node3, node4 }, type(Move::Type::INNER)
{
	if (node[0] > node[1])
	{
		std::swap(node[0], node[2]);
		std::swap(node[1], node[3]);
	}
}

bool Move::operator<(const Move& other) const
{
	if(type != other.type)
	{
		return type == Type::INNER;
	}

	for (int i = 0; i < 4; i++)
	{
		if (node[i] != other.node[i])
		{
			return node[i] < other.node[i];
		}
	}

	return false;
}
