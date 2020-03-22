#pragma once

#include <iostream>
#include <tuple>
#include <vector>

#include "ECS/Types.h"

namespace ECS
{
	class BaseSystem
	{
	public:
		virtual void Update(double deltaTime) = 0;

		//virtual void OnEntityCreated()
	};

	template<class ... ComponentTypes>
	class System : public BaseSystem
	{
		using ComponentTuple = std::tuple<std::add_pointer_t<ComponentTypes>...>;
	public:
			
	protected:
		std::vector<ComponentTuple> mComponentTuples;

	private:
			

		//template<size_t INDEX, class ComponentType, class ... ComponentArgs>
		//bool ProcessEntityComponent()
	};
}


