#pragma once
#include "node.h"

struct connection
{
	int id;
	node* startNode;
	node* stopNode;

	float weight;
};