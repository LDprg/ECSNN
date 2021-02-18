#include "nodeSytems.h"

void UpdateNodeLinear(node entity, nodelinear entityinfo)
{
	entity.output = entity.input;
}

void UpdateNodeTanh(node entity, nodetanh entityinfo)
{
	entity.output = tanh(entity.input);
}

void UpdateNodeBinary(node entity, nodebinary entityinfo)
{
	if (entity.input > entityinfo.level)
		entity.output = 1;
	else
		entity.output = 0;
}