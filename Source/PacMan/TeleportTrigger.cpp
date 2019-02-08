// Fill out your copyright notice in the Description page of Project Settings.

#include "TeleportTrigger.h"


// Sets default values
ATeleportTrigger::ATeleportTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATeleportTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleportTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleportTrigger::teleportTo(AActor * actor)
{
	actor->SetActorLocation(GetActorLocation() + relativePosToTeleport);
}

