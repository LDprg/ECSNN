#pragma once

#include "../components/node.h"

namespace ecsnn
{
	void UpdateNodeLinear(node entity, nodelinear entityinfo);
	void UpdateNodeTanh(node entity, nodetanh entityinfo);
	void UpdateNodeBinary(node entity, nodebinary entityinfo);
}