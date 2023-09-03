// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane_KeyInput.h"
#include "CP_PC_CombatPlaneController.h"

#include "GameFramework/GameModeBase.h"
#include "CP_GM_KeyInput.generated.h"

/**
 * CP_Pawn_CombatPlane_KeyInput을 DefaultPawn으로 설정하는 GM 클래스
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_GM_KeyInput : public AGameModeBase
{
	GENERATED_BODY()
	
	ACP_GM_KeyInput();

public:
	virtual void PostLogin(APlayerController* _NewPlayer) override;
};
