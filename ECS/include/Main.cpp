#include "ECS/Scene.h"
#include <iostream>
#include <vector>
#include <tuple>

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"

#include "Components/Renderable.h"
#include "Components/Transform.h"


int main()
{
	// Initialize Scene
	ECS::Scene scene;

	// Register Systems
	scene.RegisterSystem<PhysicsSystem>();
	scene.RegisterSystem<RenderSystem>();
	
	// Update Scene
	scene.Update(0.003);

	return 0;
}