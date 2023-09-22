// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CP_GM_Character.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_GM_Character : public AGameModeBase
{
	GENERATED_BODY()

	ACP_GM_Character();

public:
	virtual void PostLogin(APlayerController* _NewPlayer) override;

};
