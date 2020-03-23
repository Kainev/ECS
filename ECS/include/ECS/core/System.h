#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <unordered_map>

#include "ECS/core/Types.h"
#include "ECS/core/Component.h"
//#include "ECS/core/Scene.h"

namespace ECS
{
	class Scene;

	class BaseSystem
	{
	public:
		BaseSystem(Scene* scene) : mScene(scene) {}
		virtual void Update(double deltaTime) = 0;
	protected:
		Scene* mScene;

		//virtual void OnEntityCreated()
	};

	template<class ... ComponentTypes>
	class System : public BaseSystem
	{
		using ComponentTuple = std::tuple<std::add_pointer_t<ComponentTypes>...>;
		using EntityTupleMap = std::unordered_map<EntityId, size_t>;
	public:
		System(Scene* scene) : BaseSystem(scene) {}
	protected:
		std::vector<ComponentTuple> mComponentTuples;
		

	private:
		EntityTupleMap mEntityIdToIndexMap;

		//template<size_t INDEX, class ComponentType, class ... ComponentArgs>
		//bool ProcessEntityComponent()
	};
}


