#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MythraenGameMode.generated.h"

/**
 * Base ruleset for Mythraen maps.
 *
 * Content maps can derive a Blueprint from this class to configure player,
 * HUD, and level-specific presentation without replacing core game rules.
 */
UCLASS()
class MYTHRAEN_API AMythraenGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMythraenGameMode();
};
