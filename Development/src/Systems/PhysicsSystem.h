#pragma once

#include <iostream>
#include <tuple>

#include <ECS/ecs.h>

#include "Components/Transform.h"
#include "Components/Mesh.h"

#define GetComponent(c) std::get<c*>(tuple);
#define ComponentLoop for (auto& tuple : mComponentTuples)

class PhysicsSystem : public ECS::System<Transform, Mesh>
{
public:
	PhysicsSystem(ECS::Scene* scene) : System(scene) {}

	void Update(double deltaTime) override
	{
		ComponentLoop
		{
			Transform* transformComponent = GetComponent(Transform);
			Mesh* meshComponent = std::get<Mesh*>(tuple);

			transformComponent->y += 0.1;
			transformComponent->x += 0.1;
			transformComponent->z += 0.1;
		}
	}
};

