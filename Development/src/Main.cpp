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
#include "Components/Mesh.h"
#include "Components/Transform.h"

//#include "ECS/memory/ObjectPool.h"
#include "ECS/memory/PoolAllocator.h"
//
////#include "ECS/utility/Profiler.h"
//
//#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
//
////void Run(ECS::Scene& scene, unsigned int iterations = 10);
//


class Object
{
public:
	Object() {}

	static void* operator new(size_t size) {
		return allocator.Allocate();
	}

	static void operator delete(void* ptr, size_t size) {
		return allocator.DeAllocate(ptr);
	}

	static Pool_c allocator;
};




int main()
{
	Object::allocator = new Pool_c();
	Object::allocator.CreatePool(sizeof(Object), 64);


	//const int arraySize = 10;

	//Object* objects[arraySize];

	//{
	//	for (int i = 0; i < arraySize; ++i)
	//	{
	//		objects[i] = new Object();
	//		//std::cout << "new [" << i << "] = " << objects[i] << std::endl;
	//	}
	//}

	//for (int i = 0; i < arraySize; ++i)
	//{
	//	delete objects[i];
	//}


	//// Initialize Scene
	//ECS::Scene scene;

	//// Register Components
	//scene.RegisterComponent<Transform, 1024>();
	//scene.RegisterComponent<Mesh, 1024>();

	//// Register Systems
	//scene.RegisterSystem<PhysicsSystem>();
	//scene.RegisterSystem<RenderSystem>();

	////
	//auto playerEntity = scene.CreateEntity<Transform, Mesh>();

	//Run(scene, 100);

	return 0;
}


//void Run(ECS::Scene& scene, unsigned int iterations)
//{
//	unsigned int i = 0;
//	while(i < iterations)
//	{
//		{
//			PROFILE_SCOPE("SCENE_UPDATE");
//			scene.Update(0.003);
//		}
//		SLEEP(3);
//
//		++i;
//	}
//}
