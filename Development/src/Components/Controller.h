#pragma once

#include <ECS/ecs.h>

class Controller : public ECS::Component
{
public:
	ECS_COMPONENT_HEADER;
	Controller() {}
};
