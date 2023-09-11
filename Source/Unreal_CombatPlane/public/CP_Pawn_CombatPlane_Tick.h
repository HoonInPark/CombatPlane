// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane.h"

#include "CP_Pawn_CombatPlane_Tick.generated.h"

/**
 * 
 */

UCLASS()
class UNREAL_COMBATPLANE_API ACP_Pawn_CombatPlane_Tick : public ACP_Pawn_CombatPlane
{
	GENERATED_BODY()

public:
	ACP_Pawn_CombatPlane_Tick();

private:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	int32 Flag_InfPt;

	void MoveForward(float _DeltaTime);
	void MoveForwardAfterTakeOff(float _DeltaTime);
	void MoveForwardWhileTakeOff(float _DeltaTime);
	void MoveForwardWithCurve(float _DeltaTime);
	void MoveForwardWithInfPt(float _DeltaTime);

protected:
	enum class EPlaneState
	{
		BEFORE_45,
		AFTER_45,
		AFTER_0
	};

	EPlaneState CurrentState{ EPlaneState::BEFORE_45 };

	virtual void MoveForwardWithInfPtEnum(float _DeltaTime);
};
