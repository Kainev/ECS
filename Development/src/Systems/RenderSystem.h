#pragma once

#include <iostream>

#include <ECS/ecs.h>

#include "Components/Transform.h"


class RenderSystem : public ECS::System<Transform>
{
public:
	RenderSystem(ECS::Scene* scene) : System(scene) {}

	void Update(double deltaTime) override
	{
		//std::cout << "Render Update!" << std::endl;

		for (auto& tuple : mComponentTuples)
		{
			Transform* transformComponent = std::get<Transform*>(tuple);
		}
	}
};

