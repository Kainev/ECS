#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include <memory>

#include "Components/Transform.h"

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/InputSystem.h"

#include "Components/Renderable.h"
#include "Components/Mesh.h"

#include "Components/Controller.h"
#include "Components/RigidBody.h"

#include "ECS/utility/Profiler.h"

#include <ECS/ecs.h>

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

void Run(ECS::Scene& scene, unsigned int iterations = 10);

int main()
{
	// Initialize Scene
	ECS::Scene scene;

	// Register valid components that can be attached to entities
	scene.RegisterComponent<Transform, 1024>();
	scene.RegisterComponent<Mesh, 1024>();
	scene.RegisterComponent<RigidBody, 1024>();
	scene.RegisterComponent<Controller, 1024>();

	ECS::Entity& barrel = scene.CreateEntity<Transform, Mesh>();

	// Register Systems to act upon entities within the scene
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<InputSystem>();
	scene.RegisterSystem<RenderSystem>();

	// Creating entities: they will automatically be handled by the different systems depending on which components they have
	auto& playerEntity = scene.CreateEntity<Transform, Mesh, RigidBody, Controller>();

	scene.CreateEntity<Transform, Mesh, RigidBody>();
	scene.CreateEntity<Transform, Mesh, RigidBody>();

	return 0;
}


void Run(ECS::Scene& scene, unsigned int iterations)
{
	unsigned int i = 0;
	while(i < iterations)
	{
		{
			PROFILE_SCOPE("SCENE_UPDATE");
			scene.Update(0.003);
		}
		SLEEP(3);

		++i;
	}
}
