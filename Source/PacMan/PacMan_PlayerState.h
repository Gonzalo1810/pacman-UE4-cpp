// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PacMan_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API APacMan_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	float speed = 100;
	
	
};
