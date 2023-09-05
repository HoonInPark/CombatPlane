// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_PC_CombatPlaneController.h"
#include "CP_Character_Anim.h"
#include "GameFramework/GameModeBase.h"
#include "CP_GM_AnimInst.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_GM_AnimInst : public AGameModeBase
{
	GENERATED_BODY()

	ACP_GM_AnimInst();

public:
	virtual void PostLogin(APlayerController* _NewPlayer) override;
	
};
