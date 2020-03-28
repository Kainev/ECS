#pragma once

#include <ECS/ecs.h>

class Model;

class Mesh : public ECS::Component
{
public:
	Mesh() : mModel(nullptr) {}

	Model* mModel;
};
