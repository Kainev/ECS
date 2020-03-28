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
#include "ECS/memory/ComponentArray.h"
#include "ECS/utility/Utils.h"


namespace ECS
{
	class Scene
	{
		using Components = std::vector<std::shared_ptr<ComponentAllocator>>;
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
		Entity& CreateEntity();

		template<typename T>
		T* CreateComponent();

	private:
		ComponentTypes mComponentTypes;
		Components mComponents;
		Entities mEntities;
		Systems mSystems;

		std::queue<EntityId> mAvailableEntities;
		unsigned int mCurrentEntityCount;
		std::size_t mMaxEntites;

		template<class Component=void, class ... Components>
		void ProcessNewEntity(Entity* entity);
		
		template<>
		void ProcessNewEntity<>(Entity* entity);
	};


	inline void Scene::Update(double deltaTime)
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
		T::ID = static_cast<unsigned int>(mComponents.size());
		mComponents.push_back(std::make_shared<ComponentArray<T, MAX_COMPONENTS>>());
	}


	template<class ... Components>
	Entity& Scene::CreateEntity()
	{
		//ECS_ASSERT(mCurrentEntityCount < mMaxEntites, "ECS::ERROR::ENTITY_OVERFLOW");

		EntityId id = mAvailableEntities.front();
		mAvailableEntities.pop();
		++mCurrentEntityCount;

		Entity* entity = new Entity(0);
		mEntities.emplace(id, entity);

		ProcessNewEntity<Components...>(entity);

		for (auto& system : mSystems)
		{
			system->OnEntityCreated(*entity);
		}

		return *entity;
	}

	template<class T, class ... Components>
	void Scene::ProcessNewEntity(Entity* entity)
	{
		entity->AddComponent(mComponentTypes[typeid(T).name()], CreateComponent<T>());
		ProcessNewEntity<Components...>(entity);
	}

	template<>
	void Scene::ProcessNewEntity(Entity* entity) {}

	template<typename T>
	inline T* Scene::CreateComponent()
	{
		const char* typeName = typeid(T).name();
		auto* component = mComponents[mComponentTypes[typeName]]->Get<T>();
		return component;
	}
}