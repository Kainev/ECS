#pragma once


namespace ECS
{
	typedef unsigned int EntityId;
	typedef unsigned int ComponentId;
	typedef unsigned int ComponentType;
}


#define ECS_COMPONENT \
	public: \
		static unsigned int ID; \
	private: 