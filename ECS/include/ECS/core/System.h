#pragma once

#include <cstddef>
#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_map>

#include "ECS/core/Types.h"
#include "ECS/core/Component.h"
#include "ECS/core/Entity.h"
//#include "ECS/core/Scene.h"

namespace ECS
{
	class Scene;

	class BaseSystem
	{
	public:
		BaseSystem(Scene* scene) : mScene(scene) {}
		virtual void Update(double deltaTime) = 0;
		virtual void OnEntityCreated(const Entity& entity) = 0;
	protected:
		Scene* mScene;
	};

	template<class ... T_COMPONENTS>
	class System : public BaseSystem
	{	
	public:
		using ComponentTuple = std::tuple<std::add_pointer_t<T_COMPONENTS>...>;
		using EntityTupleMap = std::unordered_map<EntityId, size_t>;

		System(Scene* scene) : BaseSystem(scene) {}
		virtual void OnEntityCreated(const Entity& entity) override final;
	protected:
		std::vector<ComponentTuple> mComponentTuples;

	private:
		template <std::size_t T_INDEX, class T_COMPONENT_TYPE, class... Args>
		bool ProcessEntityComponent(ComponentId id, Component* component, ComponentTuple& tuple);

		template <std::size_t T_INDEX>
		bool ProcessEntityComponent(ComponentId id, Component* component, ComponentTuple& tuple);
		

	private:
		EntityTupleMap mEntityIdToIndexMap;

		//template<size_t INDEX, class ComponentType, class ... ComponentArgs>
		//bool ProcessEntityComponent()
	};


	template<class ... T_COMPONENTS>
	inline void System<T_COMPONENTS...>::OnEntityCreated(const Entity& entity)
	{
		ComponentTuple tuple;
		std::size_t matchingComponents = 0;

		for (auto& componentPair : entity.GetComponents())
		{
			if (ProcessEntityComponent<0, T_COMPONENTS...>(componentPair.first, componentPair.second, tuple))
			{
				++matchingComponents;
				if (matchingComponents == sizeof...(T_COMPONENTS))
				{
					mComponentTuples.emplace_back(std::move(tuple));
					mEntityIdToIndexMap.emplace(entity.GetId(), mComponentTuples.size() - 1);
					break;
				}
			}
		}
	}



	template<class ... T_COMPONENTS>
	template<std::size_t T_INDEX, class T_COMPONENT_TYPE, class ...Args>
	bool System<T_COMPONENTS...>::ProcessEntityComponent(ComponentId id, Component* component, ComponentTuple& tuple)
	{
		if (T_COMPONENT_TYPE::ID == id)
		{
			std::get<T_INDEX>(tuple) = static_cast<T_COMPONENT_TYPE*>(component);
			return true;
		}
		else
		{
			return ProcessEntityComponent<T_INDEX + 1, Args...>(id, component, tuple);
		}
	}

	template<class ... T_COMPONENTS>
	template<std::size_t T_INDEX>
	inline bool System<T_COMPONENTS ...>::ProcessEntityComponent(ComponentId id, Component* component, ComponentTuple& tuple)
	{
		return false;
	}


}


