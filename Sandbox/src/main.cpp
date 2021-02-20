#include "escnn.h"

#include "util.h"

#include <iostream>
#include <queue>

using namespace ecsnn;

int main()
{
	NeuralNetwork nn;

	for (int i = 0; i < 2; i++)
	{
		nn.addNode<nodeFirst, nodelinear>(0);
	}

	nn.addNode<nodeLast, nodelinear>(1);

	std::queue<float> data;
	data.emplace(0);
	data.emplace(1);

	printVector(nn.feedForward(data));

	std::cout << "End of Program." << std::endl;
	std::cin.get();
}