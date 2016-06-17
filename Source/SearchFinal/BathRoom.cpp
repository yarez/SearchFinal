// Fill out your copyright notice in the Description page of Project Settings.

#include "SearchFinal.h"
#include "BathRoom.h"
#include "SearchObj.h"


// Sets default values
ABathRoom::ABathRoom()
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/FirstPersonCPP/Blueprints/SearchObjToilet'"));
	if (ItemBlueprint.Object) {
		BP_Toilet = (UClass*)ItemBlueprint.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ABathRoom::BeginPlay()
{
	FVector Location = FVector(0, 0, 0);
	FVector Rotation = FVector(0, 0, 0);
	Super::BeginPlay();
	
	UWorld* const World = GetWorld();
	if (World) {
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		ASearchObj* Toilet = World->SpawnActor<ASearchObj>(BP_Toilet, Location, Rotation, SpawnParams);
	}
}

// Called every frame
void ABathRoom::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

