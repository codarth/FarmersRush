// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExitSpot.generated.h"

class UBoxComponent;

UCLASS()
class LOCALMULTIPLAYER_API AExitSpot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExitSpot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exit Spot")
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exit Spot")
	UStaticMeshComponent* ExitSpot_Mesh;

	// Decoration to indicate where this exit spot goes to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exit Spot")
	UStaticMeshComponent* ExitSpot_Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Exit Spot")
	bool bToMainMenu = false;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
