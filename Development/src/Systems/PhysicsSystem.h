#pragma once

#include <iostream>

#include <ECS/ecs.h>

#include "Components/Transform.h"


class PhysicsSystem : public ECS::System<Transform>
{
public:
	PhysicsSystem(ECS::Scene* scene) : System(scene) {}

	void Update(double deltaTime) override
	{
		//std::cout << "Physics Update!" << std::endl;

		for (auto& tuple : mComponentTuples)
		{

		}
	}
};

