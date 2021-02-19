#pragma once
#include "node.h"

namespace ecsnn
{
	struct connection
	{
		int id;
		node* startNode;
		node* stopNode;

		float weight;
	};
}