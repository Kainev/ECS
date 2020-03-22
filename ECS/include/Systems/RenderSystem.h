#pragma once

#include <iostream>

#include "ECS/System.h"
#include "Components/Transform.h"
#include "Components/Renderable.h"


class RenderSystem : public ECS::System<Transform, Renderable>
{
	void Update(double deltaTime) override
	{
		std::cout << "Render Update!" << std::endl;

		for (auto& tuple : mComponentTuples)
		{

		}
	}
};

