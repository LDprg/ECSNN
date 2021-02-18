#pragma once
#include <vector>
#include <queue>

#include "entt/entt.hpp"

#include "components/node.h"
#include "components/connection.h"

class NeuralNetwork
{
public:
	NeuralNetwork()
	{
	}

	/// TODO
	std::vector<float> feedForward(std::queue<float> input)
	{
		std::vector<float> output;
		auto viewFirst = registry.view<node, nodeFirst>();
		auto viewHidden = registry.view<node, nodeHidden>();
		auto viewLast = registry.view<node, nodeLast>();

		for (auto entity : viewFirst)
		{
			auto& NodeIterator = viewFirst.get<node>(entity);
			NodeIterator.input = input.front();
			input.pop();
		}

		for (auto entity : viewHidden)
		{
			auto& NodeIterator = viewFirst.get<node>(entity);
		}

		for (auto entity : viewLast)
		{
			auto& NodeIterator = viewLast.get<node>(entity);
			output.push_back(NodeIterator.output);
		}

		return output;
	}

	int addConnection(int idStartNode, int idStopNode)
	{
		auto view = registry.view<node>();

		for (auto startEntity : view)
		{
			auto& StartNodeIterator = view.get<node>(startEntity);
			if (StartNodeIterator.id == idStartNode)
			{
				for (auto stopEntity : view)
				{
					auto& StopNodeIterator = view.get<node>(stopEntity);
					if (StopNodeIterator.id == idStartNode)
					{
						auto entity = registry.create();

						connection connect{
							.id = ID,
							.startNode = &StartNodeIterator,
							.stopNode = &StopNodeIterator,
							.weight = 1
						};

						ID++;

						registry.emplace<connection>(entity, connect);

						return connect.id;
					}
				}
			}
		}
		return -1;
	}

	template <class type, class outFuncType>
	int addNode(int layer)
	{
		auto entity = newNode<type>(layer);

		registry.emplace<outFuncType>(entity);

		return ID - 1;
	}

	template <class type, class outFuncType>
	int addNode(int layer, outFuncType outType)
	{
		auto entity = newNode<type>(layer);

		registry.emplace<outFuncType>(entity, type);

		return ID - 1;
	}

	bool destroyNode(int id)
	{
		auto view = registry.view<node>();
		bool success = false;

		for (auto entity : view)
		{
			auto& NodeIterator = view.get<node>(entity);
			if (NodeIterator.id == id)
			{
				registry.destroy(entity);
				success = true;
				break;
			}
		}

		return success;
	}

private:
	entt::registry registry;
	inline static int ID = 0;

	template <class type>
	auto newNode(int layer)
	{
		auto entity = registry.create();

		node temp{
			.id = ID,
			.layer = layer,
			.input = 0,
			.output = 0
		};
		ID++;

		registry.emplace<node>(entity, temp);
		registry.emplace<type>(entity);

		return entity;
	}
};
