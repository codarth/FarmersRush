// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuCamera.generated.h"

UCLASS()
class LOCALMULTIPLAYER_API AMainMenuCamera : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainMenuCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera|Debug")
	bool bDebuggingCamera = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera|Debug")
	UStaticMeshComponent* DebugSphere;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameCamera")
	class UCameraComponent* Camera;

};
