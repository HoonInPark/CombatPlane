// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane_KeyInput.h"
#include "CP_Pawn_To_AnimInst.h"
#include "CP_Pawn_AnimInst.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_Pawn_AnimInst : public ACP_Pawn_CombatPlane_KeyInput, public ICP_Pawn_To_AnimInst
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;

private:
	virtual FPawnMovement PropellerTypeTick_Implementation() override;
	virtual FPawnMovement JetEngineTypeTick_Implementation() override;
};
