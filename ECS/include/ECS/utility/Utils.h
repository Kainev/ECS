#pragma once

#include <iostream>

#define ECS_ASSERT(x, y) { if(!(x)) { std::cout << "Assertion Failed: " << y << std::endl; __debugbreak(); } }
