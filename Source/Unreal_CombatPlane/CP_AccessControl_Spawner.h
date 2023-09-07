// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_AccessControl.h"

#include "GameFramework/Actor.h"
#include "CP_AccessControl_Spawner.generated.h"

USTRUCT(BlueprintType)
struct FHorizontalPoint 
{
	GENERATED_BODY()

	UPROPERTY()
	float Pt_X;
	UPROPERTY()
	float Pt_Y;
};

UCLASS()
class UNREAL_COMBATPLANE_API ACP_AccessControl_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACP_AccessControl_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Spawn_CP_AccessControl(const FHorizontalPoint _HorizontalPoint, float _Speed);
	
	UPROPERTY()
	int32 SpawnNum;
};
