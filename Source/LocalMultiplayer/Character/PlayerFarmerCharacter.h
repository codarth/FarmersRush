﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LocalMultiplayer/Core/Interfaces/Countdown_Interface.h"
#include "PlayerFarmerCharacter.generated.h"

class IInteract_Interface;
class AFarmersRush_GameMode;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

USTRUCT()
struct FInteractionData
{
	GENERATED_BODY()

	FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckTime(0.f)
	{
	};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckTime;
};

UCLASS()
class LOCALMULTIPLAYER_API APlayerFarmerCharacter : public ACharacter, public ICountdown_Interface
{
	GENERATED_BODY()

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//          VARIABLES
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

public:
	
	/** Camera */
	UPROPERTY()
	USpringArmComponent* SpringArm = nullptr;
	UPROPERTY()
	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraSensitivity = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float CameraZoomSensitivity = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinCameraZoom = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxCameraZoom = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinPitch = -75.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxPitch = -10.f;

	/** Player Info */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Info")
	int32 PlayerIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player Info")
	UMaterialInstance* PlayerDefaultColor;

	UPROPERTY(VisibleAnywhere, BlueprintreadWrite, Category = "Player Info")
	bool bIsPlayerReady = false;

	/** Interaction */

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	// float InteractionCheckFrequency = 0.1f;
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	// float InteractionCheckDistance = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckHalfHeight = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionCheckRadius = 50.f;

protected:

	UPROPERTY()
	AFarmersRush_GameMode* GameModeRef = nullptr;

private:
	
	// Mapping context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MappingContext;

	// Move Forward Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	// Camera Movement Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraMovementAction;

	// Zoom Camera Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomCameraAction;

	// Deactivate Player Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* DeactivatePlayerAction;

	// Interaction Input Action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping", meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractionAction;

	FTimerHandle InteractionCheckTimerHandle;

	UPROPERTY(VisibleAnywhere, Category = "Character | Interaction")
	TScriptInterface<IInteract_Interface> TargetInteractable;

	float InteractionCheckFrequency;
	float InteractionCheckDistance;
	FTimerHandle TimerHandle_Interaction;
	FInteractionData InteractionData;

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	//          FUNCTIONS
	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

public:
	
	// Sets default values for this character's properties
	APlayerFarmerCharacter();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Add camera to player when loading into the game
	UFUNCTION()
	void AddCamera();

	/** Countdown Interface */
	virtual void BeginQuitCountdown(bool bToMainMenu) override;
	virtual void UpdateQuitTimer() override;
	virtual void StopQuitCountdown() override;

	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction); }

protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game ends or when destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called for Move Forward input
	void Move(const FInputActionValue& Value);

	// Called for Rotate Camera input
	void CameraMovement(const FInputActionValue& Value);

	// Called for Zoom Camera input
	void ZoomCamera(const FInputActionValue& Value);

	// Called for Deactivate Player input
	void DeactivatePlayer(const FInputActionValue& Value);

private:
	
	void CheckForInteractable();

	void PerformInteractionCheck();
	void FoundInteractable(AActor* NewInteractable);
	void NoInteractableFound();
	void BeginInteract();
	void EndInteract();
	void Interact();

};
