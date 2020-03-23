#pragma once

#include <memory>
#include <unordered_map>

#include "ECS/core/Types.h"
#include "ECS/core/Component.h"


namespace ECS
{
	
	class Entity
	{
		using ComponentMap = std::unordered_map<ComponentId, std::shared_ptr<Component>>;

	public:
		explicit Entity(EntityId id) : mEntityId(id) {}

		EntityId GetId() const { return mEntityId; }
		const ComponentMap& GetComponents() const { return mComponents; }

	private:
		EntityId mEntityId;
		ComponentMap mComponents;
	};
}