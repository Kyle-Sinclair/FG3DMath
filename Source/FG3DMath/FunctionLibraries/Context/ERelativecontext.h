#pragma once

UENUM(BlueprintType, Meta = (Bitflags))
enum class ERelativeContext : uint8
{
	NONE ,
	Behind ,
	InFront,
	ToTheRight,
	ToTheLeft,
	Above,
	Below ,
	
};