// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

class APlayer_FR;

UCLASS()
class LOCALMULTIPLAYER_API AGameCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void CalculateCameraMovement();
	void CalculateCameraZoom();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Should debug sphere be visible
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebuggingCamera = true;
	
	// Debug sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	class UStaticMeshComponent* DebugSphere;

	// Camera boom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	class USpringArmComponent* CameraBoom;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	float MinBoom = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	float MaxBoom = 2000.f;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	class UCameraComponent* Camera;

	// Active players
	UPROPERTY()
	TArray<APlayer_FR*> ActivePlayers;

	UPROPERTY()
	bool bIsGameStarted = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	float LerpSpeed = 0.1f;
	
	UFUNCTION()
	void GameStarted(TArray<APlayer_FR*> InActivePlayers);
};
