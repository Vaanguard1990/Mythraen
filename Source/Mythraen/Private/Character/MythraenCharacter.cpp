#include "Character/MythraenCharacter.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"

AMythraenCharacter::AMythraenCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

void AMythraenCharacter::NotifyControllerChanged()
{
    Super::NotifyControllerChanged();

    const APlayerController* PlayerController = Cast<APlayerController>(Controller);
    if (PlayerController == nullptr)
    {
        return;
    }

    UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    if (Subsystem == nullptr)
    {
        return;
    }

    if (DefaultMappingContext == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s has no DefaultMappingContext assigned; player input is disabled."), *GetName());
        return;
    }

    Subsystem->AddMappingContext(DefaultMappingContext, DefaultMappingPriority);
}

void AMythraenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (EnhancedInput == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("%s expects an EnhancedInputComponent. Check DefaultInputComponentClass in DefaultInput.ini."), *GetName());
        return;
    }

    if (MoveAction != nullptr)
    {
        EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMythraenCharacter::Move);
    }

    if (LookAction != nullptr)
    {
        EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMythraenCharacter::Look);
    }

    if (JumpAction != nullptr)
    {
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
    }
}

void AMythraenCharacter::Move(const FInputActionValue& Value)
{
    if (Controller == nullptr)
    {
        return;
    }

    const FVector2D MovementInput = Value.Get<FVector2D>();
    const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    AddMovementInput(ForwardDirection, MovementInput.Y);
    AddMovementInput(RightDirection, MovementInput.X);
}

void AMythraenCharacter::Look(const FInputActionValue& Value)
{
    if (Controller == nullptr)
    {
        return;
    }

    const FVector2D LookInput = Value.Get<FVector2D>();

    AddControllerYawInput(LookInput.X);
    AddControllerPitchInput(LookInput.Y);
}
