#pragma once

#include <iostream>

#include "ECS/System.h"
#include "Components/Transform.h"


class PhysicsSystem : public ECS::System<Transform>
{
	void Update(double deltaTime) override
	{
		std::cout << "Physics Update!" << std::endl;
	}
};

