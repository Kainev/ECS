#pragma once

#include <ECS/ecs.h>

class Model;

class Mesh : public ECS::Component
{
public:
	ECS_COMPONENT_HEADER;
	Mesh() : mModel(nullptr) {}

	Model* mModel;
};
