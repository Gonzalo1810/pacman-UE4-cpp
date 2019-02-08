// Fill out your copyright notice in the Description page of Project Settings.

#include "Ghost.h"
#include <Engine.h>
#include "PathPoint.h"
#include "MainPlayer.h"
#include "Components/BoxComponent.h"

// Sets default values
AGhost::AGhost()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	haveToChangeDirection = false;


}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent * collider = dynamic_cast<UBoxComponent*>(GetComponentByClass(UBoxComponent::StaticClass()));

	if(collider)
		collider->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnBoxBeginOverlap);

	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AGhost::setStartSpeed, 1.0f, false, startTime);
	   	
}

void AGhost::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APathPoint* pathPoint = Cast<APathPoint>(OtherActor);
	if (pathPoint) 
	{
		pathDirection = getNextDirection(pathPoint);
		pathLocation = pathPoint->GetActorLocation();
		haveToChangeDirection = true;

	}
	else if (Cast<AMainPlayer>(OtherActor) !=nullptr) 
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("player!"));
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}
}

// Called every frame
void AGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorWorldOffset(direction * DeltaTime, true);

	if (haveToChangeDirection)
	{
		if (GetActorLocation().Equals(pathLocation, 1.0f))
		{
			haveToChangeDirection = false;
			SetActorLocation(pathLocation);
			changeSpeed();
		}
	}
}

void AGhost::setStartSpeed()
{
	direction = startingDirection * speed;
	pathDirection = startingDirection;
}

void AGhost::changeSpeed()
{
	direction = pathDirection * speed;
}

FVector AGhost::getNextDirection(APathPoint* pathPoint)
{
	if (pathDirection == FVector(1, 0, 0))
	{
		return pathPoint->getNextDirection(2);
	}
	else if (pathDirection == FVector(-1, 0, 0))
	{
		return pathPoint->getNextDirection(3);
	}
	else if (pathDirection == FVector(0, 1, 0))
	{
		return pathPoint->getNextDirection(0);
	}
	else if (pathDirection == FVector(0, -1, 0))
	{
		return pathPoint->getNextDirection(1);
	}

	return FVector(0, 0, 0);
}

