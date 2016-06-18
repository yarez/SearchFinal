// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SearchObj.generated.h"

UCLASS()
class SEARCHFINAL_API ASearchObj : public AActor
{
	GENERATED_BODY()
protected:
	bool isSearched;
	bool hasSearchObj;
public:	
	// Sets default values for this actor's properties
	ASearchObj();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Search();
	
};
