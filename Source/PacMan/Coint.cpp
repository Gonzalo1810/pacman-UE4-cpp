// Fill out your copyright notice in the Description page of Project Settings.

#include "Coint.h"
#include "Components/SphereComponent.h"


// Sets default values
ACoint::ACoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACoint::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ACoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACoint::contact(class AMainPlayer * player)
{

}

