// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ghost.generated.h"

UCLASS()
class PACMAN_API AGhost : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void setStartSpeed();
	void changeSpeed();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;

	FVector direction;
	float missChance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector startingDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float startTime;

	FTimerHandle UnusedHandle;

	class UBoxComponent * box;

	FVector pathDirection;
	FVector pathLocation;
	bool haveToChangeDirection;

private:
	
	FVector getNextDirection(class APathPoint* pathPoint);
	
};
