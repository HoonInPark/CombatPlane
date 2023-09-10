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

public:
	
	virtual void NativeUpdateAnimation(float _DeltaSeconds) override;

private:
	virtual void PropellerTypeTick_Implementation(FPawnMovement _PawnMovement) override;
	virtual void JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement) override;

private:
	//UPROPERTY(BlueprintReadOnly)
	FPawnMovement PawnMovement_Tick{ FRotator::ZeroRotator, 0.f };
	FPawnMovement PawnMovement_AnimInst{ FRotator::ZeroRotator, 0.f };
	
	void InterpPawnSpeed(float _DeltaSeconds, const FPawnMovement& _PawnMovement);

	float Aileron_rt;
	float Aileron_lf;
	void ProcessSpeed(const FPawnMovement& _PawnMovement);
};
