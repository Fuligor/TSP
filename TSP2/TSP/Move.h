#pragma once

struct Move
{
	enum class Type
	{
		INNER,
		OUTER
	};

	int node[6];
	Type type;
	Move(int node1, int node2, int node3, int node4, int node5, int node6);
	Move(int node1, int node2, int node3, int node4);

	bool operator < (const Move& other) const;
};

