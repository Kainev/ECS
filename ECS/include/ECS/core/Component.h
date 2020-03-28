#pragma once

#include "ECS/core/Types.h"

#define ECS_COMPONENT_HEADER static unsigned int ID
#define ECS_COMPONENT_SOURCE(CLASS) unsigned int CLASS::ID

namespace ECS
{
	class Component
	{
	public:
		Component() : mEntityId(0) {}

		void setEntityId(EntityId id) { mEntityId = id; }
		EntityId getEntityId() const { return mEntityId; }			
	private:
		EntityId mEntityId;
	};
}