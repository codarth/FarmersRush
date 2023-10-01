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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Should debug sphere be visible
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bDebuggingCamera;
	
	// Debug sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	class UStaticMeshComponent* DebugSphere;

	// Camera boom
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	// Camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* Camera;


	UFUNCTION()
	void GameStarted(TArray<APlayer_FR*> ActivePlayers);
};
