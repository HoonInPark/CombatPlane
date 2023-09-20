// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane_KeyInput.h"
#include "CP_Pawn_To_AnimInst.h"
#include "CP_Pawn_AnimInst.generated.h"

class UAnimInstance;
/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_Pawn_AnimInst : public ACP_Pawn_CombatPlane_KeyInput, public ICP_Pawn_To_AnimInst
{
	GENERATED_BODY()

	ACP_Pawn_AnimInst();

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;

private:
	virtual void PropellerTypeTick_Implementation(FPawnMovement _PawnMovement) override;
	virtual void JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement) override;

private:
	float LocalMove_Delta{ 0.f };
	float AddLocalMove(float _DeltaTime);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AnonymousBat)
	UAnimInstance* pAnimInstance;
};
