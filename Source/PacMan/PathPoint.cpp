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


/**
 * SIDE Direction where pawn come
 * @param SIDE: 0 up, 1 down, 2 left, 3 right
 */
FVector APathPoint::getNextDirection(int side)
{
	float offsetX, offsetY;

	if (player == nullptr)
		player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	offsetY = player->GetActorLocation().Y - this->GetActorLocation().Y;
	offsetX = player->GetActorLocation().X - this->GetActorLocation().X;

	if (numberOfSides == 2)
	{
		return getDirTwoSides(side);
	}
	else if (numberOfSides == 3)
	{
		return getDirThreeSides(side);
	}
	else if (numberOfSides == 4)
	{
		return getDirFourSides(side);
	}
	else GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("ERROR"));


	return FVector(0, 0, 0);
}


FVector APathPoint::getDirTwoSides(int side)
{

	if (side != 0 && up) return FVector(0, -1, 0);
	else if (side != 1 && down) return FVector(0, 1, 0);
	else if (side != 2 && left) return FVector(-1, 0, 0);
	else if (side != 3 && right) return FVector(1, 0, 0);
	else return FVector(0, 0, 0);
}

FVector APathPoint::getDirThreeSides(int side)
{
	float offsetX, offsetY;

	if (player == nullptr)
		player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	offsetY = player->GetActorLocation().Y - this->GetActorLocation().Y;
	offsetX = player->GetActorLocation().X - this->GetActorLocation().X;

	sideEnable(side, false);
	int option = calculateBetterOption(offsetX, offsetY, side);
	sideEnable(side, true);

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan,FString::Printf( TEXT("Option: %i"), option));

	switch (option)
	{
	case 0:
		return FVector(0, -1, 0);
	case 1:
		return FVector(0, 1, 0);
	case 2:
		return FVector(-1, 0, 0);
	case 3:
		return FVector(1, 0, 0);
	default:
		return FVector(0, 0, 0);
	}

}

int APathPoint::calculateBetterOption(float offsetX, float offsetY, int side)
{
	int betterOption = -1;

	if (abs(offsetX) > abs(offsetY) && (left || right))
	{
		if (offsetX >= 0)
		{
			if (right) betterOption = 3;
			else if (offsetY >= 0 && down) betterOption = 1;
			else if (up) betterOption = 0;
			else betterOption = 2;
		}
		else
		{
			if (left) betterOption = 2;
			else if (offsetY >= 0 && down) betterOption = 1;
			else if (up) betterOption = 0;
			else betterOption = 3;
		}
	}
	else
	{
		if (offsetY >= 0)
		{
			if (down) betterOption = 1;
			else if (offsetX >= 0 && right) betterOption = 3;
			else if (left) betterOption = 2;
			else betterOption = 0;
		}
		else
		{
			if (up) betterOption = 0;
			else if (offsetX >= 0 && right) betterOption = 3;
			else if (left) betterOption = 2;
			else betterOption = 1;
		}
	}


	return betterOption;
}

void APathPoint::sideEnable(int side, bool enable)
{
	switch (side)
	{
	case 0:
		up = enable;
		break;
	case 1:
		down = enable;
		break;
	case 2:
		left = enable;
		break;
	case 3:
		right = enable;
		break;
	default:
		break;
	}
}

FVector APathPoint::getDirFourSides(int side)
{
	return getDirThreeSides(side);
}

bool APathPoint::haveSide(int side)
{
	switch (side)
	{
	case 0:
		return up;
	case 1:
		return down;
	case 2:
		return left;
	case 3:
		return right;
	default:
		return false;
	}
}

