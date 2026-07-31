#include "Core/MythraenGameMode.h"

#include "Character/MythraenCharacter.h"

AMythraenGameMode::AMythraenGameMode()
{
    DefaultPawnClass = AMythraenCharacter::StaticClass();
}
