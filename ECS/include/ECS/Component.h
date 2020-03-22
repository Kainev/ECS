#pragma once

#include "ECS/Types.h"


namespace ECS
{
	class Component
	{
	public:
		Component() : mEntityId(0), mPoolIndex(0) {}

		void setEntityId(EntityId id) { mEntityId = id; }
		EntityId getEntityId() const { return mEntityId; }

		void setPoolIndex(unsigned int index) { mPoolIndex = index; }
		unsigned int getPoolIndex() const { return mPoolIndex; }
			
	private:
		EntityId mEntityId;
		unsigned int mPoolIndex;
	};
}