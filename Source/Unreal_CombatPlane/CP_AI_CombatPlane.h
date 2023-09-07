// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_To_AnimInst.h"
#include "Animation/AnimInstance.h"
#include "CP_AI_CombatPlane.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API UCP_AI_CombatPlane : public UAnimInstance, public ICP_Pawn_To_AnimInst
{
	GENERATED_BODY()
	
	UCP_AI_CombatPlane();

public:
	virtual void NativeUpdateAnimation(float _DeltaSeconds) override;

private:
	virtual FPawnMovement PropellerTypeTick_Implementation() override;
	virtual FPawnMovement JetEngineTypeTick_Implementation() override;

private:
	float PropellerRotation{ 0.f };
};
