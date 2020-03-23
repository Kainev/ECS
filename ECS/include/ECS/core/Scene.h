#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>

#include "ECS/core/Types.h"
#include "ECS/core/System.h"
#include "ECS/core/Component.h"
#include "ECS/memory/ObjectPool.h"


namespace ECS
{
	class Scene
	{
		using Components = std::vector<std::shared_ptr<IObjectPool>>;
		using ComponentTypes = std::unordered_map<const char*, ComponentType>;
		using Systems = std::vector<std::shared_ptr<BaseSystem>>;
			
	public:
		Scene() {}
		void Update(double deltaTime);

		template<typename T>
		std::shared_ptr<T> RegisterSystem();

		template<typename T, size_t MAX_COMPONENTS>
		void RegisterComponent();

	private:
		Systems mSystems;
		Components mComponents;
		ComponentTypes mComponentTypes;
	};

	void Scene::Update(double deltaTime)
	{
		for (auto& system : mSystems)
		{
			system->Update(deltaTime);
		}
	}

	template<class T>
	inline std::shared_ptr<T> Scene::RegisterSystem()
	{
		const char* typeName = typeid(T).name();
		auto system = std::make_shared<T>(this);
		mSystems.push_back(system);

		return system;
	}


	template<typename T, size_t MAX_COMPONENTS>
	inline void Scene::RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		mComponentTypes[typeName] = mComponents.size();
		mComponents.push_back(std::make_shared<ObjectPool<T, MAX_COMPONENTS>>());
	}

}
