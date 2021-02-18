#include "nodeSytems.h"

void ecsnn::UpdateNodeLinear(node entity, nodelinear entityinfo)
{
	entity.output = entity.input;
}

void ecsnn::UpdateNodeTanh(node entity, nodetanh entityinfo)
{
	entity.output = tanh(entity.input);
}

void ecsnn::UpdateNodeBinary(node entity, nodebinary entityinfo)
{
	if (entity.input > entityinfo.level)
		entity.output = 1;
	else
		entity.output = 0;
}