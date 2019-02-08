// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Coint.generated.h"

UCLASS()
class PACMAN_API ACoint : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ACoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int getScore() { return score; }

	virtual void contact(class AMainPlayer * player);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int score = 10;

	
};
