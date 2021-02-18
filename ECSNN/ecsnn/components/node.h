#pragma once
#include "..\core.h"

namespace ecsnn
{
	struct nodeFirst
	{
	};

	struct nodeHidden
	{
	};

	struct nodeLast
	{
	};

	struct nodelinear
	{
	};

	struct nodetanh
	{
	};

	struct nodebinary
	{
		float level;
	};

	struct node
	{
		int layer;

		float input;
		float output;
	};
}