// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportTrigger.generated.h"

UCLASS()
class PACMAN_API ATeleportTrigger : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATeleportTrigger * conection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector relativePosToTeleport;
		
public:	
	// Sets default values for this actor's properties
	ATeleportTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void teleportTo(AActor * actor);
	
};
