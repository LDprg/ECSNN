#pragma once
#include <iostream>
#include <vector>

template<typename T>
inline std::vector<T>& printVector(std::vector<T>& input)
{
	for (auto& var : input)
	{
		std::cout << var << std::endl;
	}

	return input;
}