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
		std::vector<float> feedForward(std::queue<float>& input)
		{
			std::vector<float> output;
			auto viewFirst = registry.view<node, nodeFirst>();
			//auto viewHidden = registry.view<node, nodeHidden>();
			auto viewLast = registry.view<node, nodeLast>();

			ResetNet();

			for (auto entity : viewFirst)
			{
				auto& NodeIterator = viewFirst.get<node>(entity);
				NodeIterator.input = input.front();
				input.pop();
			}

			/*for (auto entity : viewHidden)
			{
				auto& NodeIterator = viewFirst.get<node>(entity);
			}*/

			for (auto entity : viewLast)
			{
				auto& NodeIterator = viewLast.get<node>(entity);
				output.push_back(NodeIterator.output);
			}

			return output;
		}

		void ResetNet()
		{
			auto view = registry.group<node>(entt::exclude<nodeFirst>);

			for (auto entity : view)
			{
				auto& NodeIterator = view.get<node>(entity);
				NodeIterator.input = 0;
			}
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

		template <typename type, typename outFuncType>
		int addNode(int layer)
		{
			auto entity = newNode<type>(layer);

			registry.emplace<outFuncType>(entity);

			return registry.view<node>().get<node>(entity).id;
		}

		template <typename type, typename outFuncType>
		int addNode(int layer, outFuncType outType)
		{
			auto entity = newNode<type>(layer);

			registry.emplace<outFuncType>(entity, type);

			return registry.view<node>().get<node>(entity).id;
		}

		void destroyConnection(ID id)
		{
			registry.destroy(id);
		}

		void destroyNode(ID id)
		{
			auto view = registry.view<connection>();
			auto& Node = registry.view<node>().get<node>(id);

			for (auto entity : view)
			{
				auto& ConnectionIterator = view.get<connection>(entity);

				if (ConnectionIterator.startNode->id == Node.id)
				{
					registry.destroy(entity);
				}

				if (ConnectionIterator.stopNode->id == Node.id)
				{
					registry.destroy(entity);
				}
			}

			registry.destroy(id);
		}

	private:
		inline static int ID = 0;
		entt::registry registry;

		template <typename type>
		auto newNode(int layer)
		{
			auto entity = registry.create();

			node temp{
				.id = ID,
				.layer = layer,
				.input = 0,
				.output = 0
			};

			++ID;

			registry.emplace<node>(entity, temp);
			registry.emplace<type>(entity);

			return entity;
		}
	};
}