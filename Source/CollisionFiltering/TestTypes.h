#pragma once

#include "CoreMinimal.h"
#include "Engine/EngineTypes.h"
#include "TestTypes.generated.h"

/*
Collision/Query Filtering adjusted to:
IF((~Mask0 & ~Mask1)&63 == 0)
{
	IGNORE
}
Done this way to preserve full interaction with default mask value of 0, otherwise would need to make default MAX VALUE
Should set SetMoveIgnoreMask == SetMaskFilterOnBodyInstance for consistent handling
*/
UENUM()
enum class EMaskFilterChannels : uint8
{
	ALL = 0, //Interact with everything
	IGNORE_ALL = 63, //Interact with nothing
	//Single Channel Interaction Masks, can get interactions across multiple channels by &ing them: REDTEAM = CHN1, BLUETEAM = CHN2, PURPLETEAM = READTEAM & BLUETEAM
	CHANNEL1 = IGNORE_ALL ^ (1 << 0),
	CHANNEL2 = IGNORE_ALL ^ (1 << 1),
	CHANNEL3 = IGNORE_ALL ^ (1 << 2),
	CHANNEL4 = IGNORE_ALL ^ (1 << 3),
	CHANNEL5 = IGNORE_ALL ^ (1 << 4),
	CHANNEL6 = IGNORE_ALL ^ (1 << 5)
};