// Fill out your copyright notice in the Description page of Project Settings.

#include "SearchFinal.h"
#include "SearchObj.h"


// Sets default values
ASearchObj::ASearchObj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isSearched = false;
	hasSearchObj = true;
}

// Called when the game starts or when spawned
void ASearchObj::BeginPlay()
{
	Super::BeginPlay();
}

void ASearchObj::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
}

void ASearchObj::Search()
{
	if (!isSearched) {
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, TEXT("OW"));
		isSearched = true;
	} else {
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Red, TEXT("Already Searched"));
	}
}
