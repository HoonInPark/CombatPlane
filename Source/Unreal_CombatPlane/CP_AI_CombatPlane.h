// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Character_To_AnimInst.h"
#include "Animation/AnimInstance.h"
#include "CP_AI_CombatPlane.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API UCP_AI_CombatPlane : public UAnimInstance, public ICP_Character_To_AnimInst
{
	GENERATED_BODY()
	
	UCP_AI_CombatPlane();
	void SpinPropeller();
	void MoveAileron();

public:
	virtual void NativeUpdateAnimation(float _DeltaSeconds) override;

private:
	 virtual void PropellerTypeTick_Implementation() override;
	 virtual void JetEngineTypeTick_Implementation() override;

};