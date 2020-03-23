#pragma once

#include <iostream>

#include <ECS/ecs.h>

#include "Components/Transform.h"
#include "Components/Renderable.h"


class RenderSystem : public ECS::System<Transform, Renderable>
{
public:
	RenderSystem(ECS::Scene* scene) : System(scene) {}

	void Update(double deltaTime) override
	{
		//std::cout << "Render Update!" << std::endl;

		for (auto& tuple : mComponentTuples)
		{

		}
	}
};

