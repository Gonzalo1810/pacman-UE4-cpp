// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "PathPoint.generated.h"

UCLASS()
class PACMAN_API APathPoint : public ATriggerBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/**
	 * SIDE Direction where pawn come
	 * @param SIDE: 0 up, 1 down, 2 left, 3 right
	 */
	FVector getNextDirection(int side);

	bool haveSide(int side);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor * player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int numberOfSides;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool up;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool down;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool right;

private:

	FVector getDirTwoSides(int side);
	FVector getDirThreeSides(int side);
	FVector getDirFourSides(int side);
	int calculateBetterOption(float offsetX, float offsetY,int side);
	void sideEnable(int side, bool enable);
	
};
