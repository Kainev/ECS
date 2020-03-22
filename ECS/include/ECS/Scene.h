#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "ECS/Types.h"
#include "ECS/System.h"
#include "ECS/Component.h"


namespace ECS
{
	class Scene
	{
		using Components = std::vector<std::vector<std::shared_ptr<Component>>>;
		using Systems = std::vector<std::shared_ptr<BaseSystem>>;
			
	public:
		Scene() {}
		void Update(double deltaTime);

		template<typename T>
		std::shared_ptr<T> RegisterSystem();


	private:
		Systems mSystems;
		Components mComponents;
	};

	void Scene::Update(double deltaTime)
	{
		for (auto& system : mSystems)
		{
			system->Update(deltaTime);
		}
	}

	template<typename T>
	std::shared_ptr<T> Scene::RegisterSystem()
	{
		const char* typeName = typeid(T).name();
		auto system = std::make_shared<T>();
		mSystems.push_back(system);

		return system;
	}
}
