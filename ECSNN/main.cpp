#include <iostream>

#include "NeuralNetwork.h"

int main()
{
	NeuralNetwork nn;

	for (int i = 0; i < 2; i++)
	{
		nn.addNode<nodeFirst, nodelinear>(0);
	}

	nn.addNode<nodeLast, nodelinear>(1);

	//	std::cin.get();
}