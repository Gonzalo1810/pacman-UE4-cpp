// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayer.h"
#include "PathPoint.h"
#include "Components/SphereComponent.h"
#include <Engine.h>
#include "Components/InputComponent.h"
#include "PacMan_PlayerState.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	direction = FVector(0, 0, 0);
	haveToChangeDirection = false;

	
	collider = NewObject<USphereComponent>(this, TEXT("Trigger Sphere"));
	collider->InitSphereRadius(5.f);
	collider->RegisterComponent();

	collider->OnComponentBeginOverlap.AddDynamic(this, &AMainPlayer::BeginOverlap);

}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController * controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	speed = 200;
	direction = FVector(speed, 0, 0);

	currentDirection = RIGHT;
	nextDirection = RIGHT;


	EnableInput(controller);
}

// Called every frame
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

	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("COLLISION"));
	APathPoint* pathPoint = Cast<APathPoint>(OtherActor);
	if (pathPoint)
	{
		pathPointPosition = pathPoint->GetActorLocation();
		haveToChangeDirection = true;
	}
}

void AMainPlayer::changeDirection()
{
	switch (nextDirection)
	{
	case UP:
		currentDirection = UP;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("up"));
		direction = FVector(0, -speed, 0);
		break;
	case DOWN:
		currentDirection = DOWN;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("dow"));
		direction = FVector(0, speed, 0);
		break;
	case LEFT:
		currentDirection = LEFT;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("l"));
		direction = FVector(-speed, 0, 0);
		break;
	case RIGHT:
		currentDirection = RIGHT;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("r"));
		direction = FVector(speed, 0, 0);
		break;
	default:
		break;
	}
}



// Called to bind functionality to input
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
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("up!"));
		direction = FVector(0, -speed, 0);
		currentDirection = UP;
	}
	
	nextDirection = UP;
	
}

void AMainPlayer::GoDown()
{
	if (currentDirection == UP)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("down!"));
		direction = FVector(0, speed, 0);
		currentDirection = DOWN;
	}
	
	nextDirection = DOWN;
	
}

void AMainPlayer::GoLeft()
{
	if (currentDirection == RIGHT)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("left!"));
		direction = FVector(-speed, 0, 0);
		currentDirection = LEFT;
	}
	
	nextDirection = LEFT;
	
}

void AMainPlayer::GoRight()
{
	if (currentDirection == LEFT)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("right!"));
		direction = FVector(speed, 0, 0);
		currentDirection = RIGHT;
	}
	
	nextDirection = RIGHT;
}

