// Fill out your copyright notice in the Description page of Project Settings.


#include "VelocityBoostCoint.h"
#include "MainPlayer.h"
#include <Engine.h>



void AVelocityBoostCoint::contact(AMainPlayer * player)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("FREEZE"));
	player->boostSpeed(boostSpeed, time);
}



