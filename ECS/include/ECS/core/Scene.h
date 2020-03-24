#pragma once

#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <queue>


#include "ECS/core/Types.h"
#include "ECS/core/System.h"
#include "ECS/core/Entity.h"
#include "ECS/core/Component.h"
#include "ECS/memory/ObjectPool.h"
#include "ECS/utility/Utils.h"


namespace ECS
{
	class Scene
	{
		using Components = std::vector<std::shared_ptr<IObjectPool>>;
		using ComponentTypes = std::unordered_map<const char*, ComponentType>;
		using Systems = std::vector<std::shared_ptr<BaseSystem>>;
		using Entities = std::unordered_map<EntityId, std::shared_ptr<Entity>>;
			
	public:
		Scene(std::size_t maxEntities = std::size_t(4096)) : mMaxEntites(maxEntities), mCurrentEntityCount(0)
		{
			for (EntityId id = 0; id < maxEntities; ++id)
			{
				mAvailableEntities.push(id);
			}
		}
		void Update(double deltaTime);

		template<typename T>
		std::shared_ptr<T> RegisterSystem();

		template<typename T, std::size_t MAX_COMPONENTS>
		void RegisterComponent();

		template<class ... Components>
		std::shared_ptr<Entity> CreateEntity();

		//template<typename T>
		//std::shared_ptr<T> CreateComponent();

	private:
		ComponentTypes mComponentTypes;
		Components mComponents;
		Entities mEntities;
		Systems mSystems;

		std::queue<EntityId> mAvailableEntities;
		unsigned int mCurrentEntityCount;
		std::size_t mMaxEntites;

		template<class Component=void, class ... Components>
		void ProcessNewEntity();

		template<>
		void ProcessNewEntity<>();
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


	template<typename T, std::size_t MAX_COMPONENTS>
	inline void Scene::RegisterComponent()
	{
		const char* typeName = typeid(T).name();
		mComponentTypes[typeName] = static_cast<unsigned int>(mComponents.size());
		mComponents.push_back(std::make_shared<ObjectPool<T, MAX_COMPONENTS>>());
	}


	template<class ... Components>
	std::shared_ptr<Entity> Scene::CreateEntity()
	{
		ECS_ASSERT(mCurrentEntityCount < mMaxEntites, "ECS::ERROR::ENTITY_OVERFLOW");

		EntityId id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mCurrentEntityCount;

		std::shared_ptr<Entity> entity = std::make_shared<Entity>(id);
		mEntities.emplace(id, entity);

		ProcessNewEntity<Components...>();

		return entity;
	}


	template<class Component, class ... Components>
	void Scene::ProcessNewEntity()
	{
		std::cout << "Process 1" << std::endl;
		ProcessNewEntity<Components...>();
	}

	template<>
	void Scene::ProcessNewEntity()
	{
		std::cout << "Processed!" << std::endl;
	}

	//template<typename T>
	//inline std::shared_ptr<T> Scene::CreateComponent()
	//{
	//	const char* typeName = typeid(T).name();
	//	std::shared_ptr<T> component = std::make_shared<T>();
	//	mComponents[mComponentTypes[typeName]].


	//	return std::shared_ptr<T>();
	//}
}
