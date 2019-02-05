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

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	box->OnComponentBeginOverlap.AddDynamic(this, &AGhost::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void AGhost::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("1!"));
	GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &AGhost::setStartSpeed, 1.0f, true, startTime);
	
}

void AGhost::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	APathPoint* pathPoint = Cast<APathPoint>(OtherActor);
	if (pathPoint) 
	{
		pathDirection = pathPoint->getDirection();
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
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("2!"));
}

void AGhost::changeSpeed()
{
	direction = pathDirection * speed;
}

