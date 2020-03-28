#pragma once

#include <ECS/ecs.h>



class Transform : public ECS::Component
{
public:
	static unsigned int ID;

public:
	Transform() : x(0.0f), y(0.0f), z(0.0f) { }

	float x;
	float y;
	float z;
};
