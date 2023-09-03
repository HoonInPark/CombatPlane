// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "GameFramework/PlayerController.h"
#include "CP_PC_CombatPlaneController.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_PC_CombatPlaneController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* _APawn) override;
};
