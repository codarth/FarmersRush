// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerStartSpot.generated.h"

class UBoxComponent;

UCLASS()
class LOCALMULTIPLAYER_API APlayerStartSpot : public AActor
{
	GENERATED_BODY()

	APlayerStartSpot();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	UBoxComponent* OverlapBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	UStaticMeshComponent* StartSpot_Plane;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	TArray<UMaterialInstance*> PlayerMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Info")
	UMaterialInstance* DefaultMaterial;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
