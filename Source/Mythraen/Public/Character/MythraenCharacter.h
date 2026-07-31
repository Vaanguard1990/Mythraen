#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MythraenCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Base third-person player character. Gameplay capabilities are intentionally
 * added through components as the project grows.
 */
UCLASS()
class MYTHRAEN_API AMythraenCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMythraenCharacter();

    UFUNCTION(BlueprintPure, Category = "Camera")
    USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    UFUNCTION(BlueprintPure, Category = "Camera")
    UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;
};
