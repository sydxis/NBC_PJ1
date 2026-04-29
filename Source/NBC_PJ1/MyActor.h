// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class NBC_PJ1_API AMyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void Move(int32 Index);
	void Turn(int32 Index);
	float TotalDistance = 0.0f;
	int32 MoveCount = 0;
	int32 TurnCount = 0;
	FVector PrevLocation = FVector::ZeroVector;

};
