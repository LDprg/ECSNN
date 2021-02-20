#pragma once
#include "ecsnn\core.h"
#include "node.h"

namespace ecsnn
{
	struct connection
	{
		node* startNode;
		node* stopNode;

		float weight;
	};
}