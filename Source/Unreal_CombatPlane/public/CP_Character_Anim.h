// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "GameFramework/Character.h"
#include "CP_Character_Anim.generated.h"

UCLASS()
class UNREAL_COMBATPLANE_API ACP_Character_Anim : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACP_Character_Anim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
