// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "GameFramework/Pawn.h"
#include "CP_Pawn_CombatPlane.generated.h"

UCLASS()
class UNREAL_COMBATPLANE_API ACP_Pawn_CombatPlane : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACP_Pawn_CombatPlane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CombatPlane)
	USkeletalMeshComponent* pBodyMeshComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=CombatPlane)
	UCameraComponent* pCamera;

	int32 CallNum;
};
