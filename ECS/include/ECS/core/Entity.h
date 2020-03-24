#pragma once

#include <memory>
#include <unordered_map>

#include "ECS/core/Types.h"
#include "ECS/core/Component.h"
#include "ECS/utility/Utils.h"


namespace ECS
{
	
	class Entity
	{
		using ComponentMap = std::unordered_map<ComponentId, std::shared_ptr<Component>>;

	public:
		explicit Entity(EntityId id) : mEntityId(id) {}

		void AddComponent(ComponentId id, std::shared_ptr<Component> component);

		EntityId GetId() const { return mEntityId; }
		const ComponentMap& GetComponents() const { return mComponents; }

	private:
		EntityId mEntityId;
		ComponentMap mComponents;
	};

	void Entity::AddComponent(ComponentId id, std::shared_ptr<Component> component)
	{
		ECS_ASSERT(mComponents.find(id) == mComponents.end(), "Duplicate Component!");
		mComponents.emplace(id, component);
	}
}