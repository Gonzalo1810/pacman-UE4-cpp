// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MainPlayer.generated.h"

UCLASS()
class PACMAN_API AMainPlayer : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);


	void changeDirection();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GoUp();
	void GoDown();
	void GoLeft();
	void GoRight();


protected:

	enum Direction
	{
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3
	};

	Direction currentDirection;
	Direction nextDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float startSpeed = 300;

	float speed;

	FVector direction;
	FVector pathPointPosition;
	bool haveToChangeDirection;

	class USphereComponent * collider;

	bool isStopped;
	class APathPoint * pathPointOverlap;
	bool haveToStop;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int totalScore;

	class APlayerController *  controller;

	FTimerHandle UnusedHandle;

public:
	
	UFUNCTION(BlueprintNativeEvent, Category = "Score")
	void addScore(int score);

	void setSpeed(float newSpeed) { speed = newSpeed; }
	float getSpeed()const { return speed; }

	void boostSpeed(float newSpeed, float time);
	void normalSpeed();

	
};
