#pragma once

#include <memory>
#include <unordered_map>

#include "ECS/core/Types.h"
#include "ECS/core/Component.h"
#include "ECS/memory/ComponentArray.h"
#include "ECS/utility/Utils.h"


namespace ECS
{
	
	class Entity
	{
		using ComponentMap = std::unordered_map<ComponentId, Component*>;

	public:
		explicit Entity(EntityId id) : mEntityId(id) {}

		void AddComponent(ComponentType id, Component* component)
		{
			ECS_ASSERT(mComponents.find(id) == mComponents.end(), "Duplicate or unregistered component!");
			mComponents.emplace(id, component);
		}

		EntityId GetId() const { return mEntityId; }
		const ComponentMap& GetComponents() const { return mComponents; }
		
		template<class T>
		const T* GetComponent()
		{
			return static_cast<T*>(mComponents[T::ID]);
		}

	private:
		EntityId mEntityId;
		ComponentMap mComponents;
	};
}