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

#include "Components/Mesh.h"
#include "Components/Controller.h"

#include "ECS/utility/Profiler.h"

#include <ECS/ecs.h>

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

int main()
{
	// Initialize Scene
	ECS::Scene scene;

	// Register valid components that can be attached to entities
	scene.RegisterComponent<Transform, 6000>();
	scene.RegisterComponent<Mesh, 6000>();
	scene.RegisterComponent<Controller, 6000>();



	// Register Systems to act upon entities within the scene
	scene.RegisterSystem<PhysicsSystem>();
	//scene.RegisterSystem<InputSystem>();
	scene.RegisterSystem<RenderSystem>();

	// Creating entities: they will automatically be handled by the different systems depending on which components they have
	{
		PROFILE_SCOPE("Create Entities");
		for (int i = 0; i < 5000; i++)
		{
			scene.CreateEntity<Transform, Mesh, Controller>();
		}
	}


	//scene.CreateEntity<Transform, Mesh>();
	//scene.CreateEntity<Transform, Mesh>();

	unsigned int i = 0;
	while (i < 100)
	{
		{
			PROFILE_SCOPE("UPDATE");
			scene.Update(0.003);
		}
		SLEEP(3);

		++i;
	}

	return 0;
}
