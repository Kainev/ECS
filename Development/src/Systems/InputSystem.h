#pragma once

#include <iostream>

#include <ECS/ecs.h>

#include "Components/Transform.h"

class InputSystem : public ECS::System<Transform>
{
public:
	InputSystem(ECS::Scene* scene) : System(scene) {}

	void Update(double deltaTime) override
	{
		//std::cout << "Render Update!" << std::endl;

		for (auto& tuple : mComponentTuples)
		{

		}
	}
};

