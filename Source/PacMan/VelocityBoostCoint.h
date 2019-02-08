// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Coint.h"
#include "VelocityBoostCoint.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AVelocityBoostCoint : public ACoint
{
	GENERATED_BODY()

protected:
	float playerSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float boostSpeed = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float time = 3;

public:

	void contact(class AMainPlayer * player) override;
	
	
};
