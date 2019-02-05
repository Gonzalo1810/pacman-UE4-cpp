// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayer.h"
#include "PathPoint.h"
#include "Components/SphereComponent.h"
#include <Engine.h>
#include "Components/InputComponent.h"
#include "PacMan_PlayerState.h"


AMainPlayer::AMainPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	direction = FVector(0, 0, 0);
	haveToChangeDirection = false;
	isStopped = false;
	isOnPathPoint = false;

}


void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController * controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	speed = 200;
	direction = FVector(speed, 0, 0);

	currentDirection = RIGHT;
	nextDirection = RIGHT;


	collider = dynamic_cast<USphereComponent*>(GetComponentByClass(USphereComponent::StaticClass()));
	if (collider)
		collider->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayer::BeginOverlap);
	

	EnableInput(controller);
}


void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(direction * DeltaTime, true);

	if (haveToChangeDirection)
	{
		if (GetActorLocation().Equals(pathPointPosition, 1.0f))
		{
			haveToChangeDirection = false;
			SetActorLocation(pathPointPosition);
			changeDirection();
		}
	}

}

void AMainPlayer::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	APathPoint* pathPoint = Cast<APathPoint>(OtherActor);
	if (pathPoint)
	{
		isOnPathPoint = true;
		pathPointOverlap = pathPoint;
		if (!pathPoint->haveSide(nextDirection) && !pathPoint->haveSide(currentDirection))
		{
			isStopped = true;
			pathPointOverlap = pathPoint;
			pathPointPosition = pathPoint->GetActorLocation();
		}
		else
		{
			pathPointPosition = pathPoint->GetActorLocation();
			haveToChangeDirection = true;
		}
	}
}


void AMainPlayer::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	isOnPathPoint = false;
}


void AMainPlayer::changeDirection()
{
	switch (nextDirection)
	{
	case UP:
		currentDirection = UP;
		direction = FVector(0, -speed, 0);
		break;
	case DOWN:
		currentDirection = DOWN;
		direction = FVector(0, speed, 0);
		break;
	case LEFT:
		currentDirection = LEFT;
		direction = FVector(-speed, 0, 0);
		break;
	case RIGHT:
		currentDirection = RIGHT;
		direction = FVector(speed, 0, 0);
		break;
	default:
		break;
	}
}


void AMainPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAction("Up", IE_Pressed, this, &AMainPlayer::GoUp);
	InputComponent->BindAction("Down", IE_Pressed, this, &AMainPlayer::GoDown);
	InputComponent->BindAction("Left", IE_Pressed, this, &AMainPlayer::GoLeft);
	InputComponent->BindAction("Right", IE_Pressed, this, &AMainPlayer::GoRight);
}


void AMainPlayer::GoUp() 
{
	if (currentDirection == DOWN)
	{
		direction = FVector(0, -speed, 0);
		currentDirection = UP;
	}
	else if (isStopped && pathPointOverlap->haveSide(UP))
	{
		isStopped = false;
		haveToChangeDirection = false;
		SetActorLocation(pathPointPosition);
		direction = FVector(0, -speed, 0);
		currentDirection = UP;
	}

	nextDirection = UP;
}

void AMainPlayer::GoDown()
{
	if (currentDirection == UP)
	{
		direction = FVector(0, speed, 0);
		currentDirection = DOWN;
	}
	else if (isStopped && pathPointOverlap->haveSide(DOWN))
	{
		isStopped = false;
		haveToChangeDirection = false;
		SetActorLocation(pathPointPosition);
		direction = FVector(0, speed, 0);
		currentDirection = DOWN;
	}
	
	nextDirection = DOWN;
	
}

void AMainPlayer::GoLeft()
{
	if (currentDirection == RIGHT)
	{
		direction = FVector(-speed, 0, 0);
		currentDirection = LEFT;
	}
	else if (isStopped && pathPointOverlap->haveSide(LEFT))
	{
		isStopped = false;
		haveToChangeDirection = false;
		SetActorLocation(pathPointPosition);
		direction = FVector(-speed, 0, 0);
		currentDirection = LEFT;
	}
	
	nextDirection = LEFT;
	
}

void AMainPlayer::GoRight()
{
	if (currentDirection == LEFT)
	{
		direction = FVector(speed, 0, 0);
		currentDirection = RIGHT;
	}
	else if (isStopped && pathPointOverlap->haveSide(RIGHT))
	{
		isStopped = false;
		haveToChangeDirection = false;
		SetActorLocation(pathPointPosition);
		direction = FVector(speed, 0, 0);
		currentDirection = RIGHT;
	}

	nextDirection = RIGHT;
}

