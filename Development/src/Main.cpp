#include <iostream>
#include <vector>
#include <tuple>
#include <thread>
#include <chrono>
#include <memory>

#include <ECS/ecs.h>

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"

#include "Components/Renderable.h"
#include "Components/Transform.h"

#include "ECS/memory/ObjectPool.h"

#include "ECS/utility/Profiler.h"

#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));

void Run(ECS::Scene& scene, unsigned int iterations = 10);


int main()
{
	// Initialize Scene
	ECS::Scene scene;

	// Register Systems
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	scene.RegisterSystem<RenderSystem>();
	
	Run(scene, 200);
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

