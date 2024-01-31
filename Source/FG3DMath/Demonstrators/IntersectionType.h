#pragma once

#include "CoreMinimal.h"

UENUM()
enum EIntersectionType
{
	Plane,
	Sphere,
	AABB,
	Triangle,
	Ray
};
