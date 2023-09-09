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
	virtual void PropellerTypeTick_Implementation(FPawnMovement _PawnMovement) override;
	virtual void JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement) override;

private:
	float PropellerRotation{ 0.f };

	// 다음 변수들은 
public:
	// 가속도를 결정할 것이다
	UPROPERTY(BlueprintReadOnly)
	float Multiplier_Propeller;
	// 각도와 곱해줄 것이다.
	UPROPERTY(BlueprintReadOnly)
	float Multiplier_Aileron;
};
