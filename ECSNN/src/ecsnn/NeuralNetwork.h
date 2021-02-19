#pragma once

#include "entt.hpp"

#include "components/node.h"
#include "components/connection.h"
#include "core.h"

namespace ecsnn
{
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

		ID addConnection(ID idStartNode, ID idStopNode)
		{
			auto view = registry.view<node>();
			auto entity = registry.create();

			auto& startNode = view.get<node>(idStartNode);
			auto& stopNode = view.get<node>(idStopNode);

			connection connect{
				.startNode = &startNode,
				.stopNode = &stopNode,
				.weight = 1
			};

			registry.emplace<connection>(entity, connect);

			return entity;
		}

		template <class type, class outFuncType>
		ID addNode(int layer)
		{
			auto entity = newNode<type>(layer);

			registry.emplace<outFuncType>(entity);

			return entity;
		}

		template <class type, class outFuncType>
		ID addNode(int layer, outFuncType outType)
		{
			auto entity = newNode<type>(layer);

			registry.emplace<outFuncType>(entity, type);

			return entity;
		}

		void destroyNode(ID id)
		{
			registry.destroy(id);
		}

	private:
		entt::registry registry;

		template <class type>
		auto newNode(int layer)
		{
			auto entity = registry.create();

			node temp{
				.layer = layer,
				.input = 0,
				.output = 0
			};

			registry.emplace<node>(entity, temp);
			registry.emplace<type>(entity);

			return entity;
		}
	};
}