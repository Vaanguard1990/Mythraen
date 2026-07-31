#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MythraenCharacter.generated.h"

class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
struct FInputActionValue;

/**
 * Base third-person player character. Gameplay capabilities are intentionally
 * added through components as the project grows.
 *
 * Input is driven by Enhanced Input. The mapping context and actions are left
 * unset in C++ so content assigns them on a derived Blueprint.
 */
UCLASS()
class MYTHRAEN_API AMythraenCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMythraenCharacter();

    virtual void NotifyControllerChanged() override;

    UFUNCTION(BlueprintPure, Category = "Camera")
    USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    UFUNCTION(BlueprintPure, Category = "Camera")
    UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    /** Moves the character along the control-rotation-relative ground plane. */
    void Move(const FInputActionValue& Value);

    /** Adds yaw and pitch input, which the camera boom follows. */
    void Look(const FInputActionValue& Value);

    /** Mapping context applied while this character is locally controlled. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    /** Priority used when applying DefaultMappingContext. Higher values win. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    int32 DefaultMappingPriority = 0;

    /** Axis2D action: X strafes, Y moves forward. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;

    /** Axis2D action: X yaws, Y pitches. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> LookAction;

    /** Digital action bound to the engine jump. */
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputAction> JumpAction;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UCameraComponent> FollowCamera;
};
