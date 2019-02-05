// Fill out your copyright notice in the Description page of Project Settings.

#include "PathPoint.h"
#include <Engine.h>


// Sets default values
APathPoint::APathPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APathPoint::BeginPlay()
{
	Super::BeginPlay();
	player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
}

// Called every frame
void APathPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector APathPoint::getDirection()
{
	float offsetX, offsetY;

	if (player == nullptr)
		player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	offsetY = player->GetActorLocation().Y - this->GetActorLocation().Y;
	offsetX = player->GetActorLocation().X - this->GetActorLocation().X;

	if (abs(offsetX) > abs(offsetY)) 
	{
		if (offsetX >= 0)
		{
			return FVector(1, 0, 0);
		}
		else
		{
			return FVector(-1, 0, 0);
		}
	}
	else
	{
		if (offsetY >= 0)
		{
			return FVector(0, 1, 0);
		}
		else
		{
			return FVector(0, -1, 0);
		}
	}
}

FVector APathPoint::getNextDirection()
{
	float offsetX, offsetY;

	if (player == nullptr)
		player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	offsetY = player->GetActorLocation().Y - this->GetActorLocation().Y;
	offsetX = player->GetActorLocation().X - this->GetActorLocation().X;



	return FVector(0, 1, 0);
}

