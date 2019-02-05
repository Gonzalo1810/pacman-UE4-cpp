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
		return getDirFourSides();
	}


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

	if (abs(offsetX) > abs(offsetY))
	{
		if (left && right)
		{
			if(offsetX >= 0) return FVector(1, 0, 0);
			else return FVector(-1, 0, 0);
		}
		else if (!left && offsetX < 0 || !right && offsetX >= 0)
		{
			if (offsetY >= 0) return FVector(0, 1, 0);
			else return FVector(0, -1, 0);
		}
	}
	else
	{
		if (up && down)
		{
			if (offsetY >= 0) return FVector(0, 1, 0);
			else return FVector(0, -1, 0);
		}
		else if (!up && offsetY < 0 || !down && offsetY >= 0)
		{
			if (offsetX >= 0) return FVector(1, 0, 0);
			else return FVector(-1, 0, 0);
		}
	}

	return FVector(0, 0, 0);
}

FVector APathPoint::getDirFourSides()
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

