// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_AI_CombatPlane.h"

// AnimInstance에서의 Tick의 역할을 하는 함수
void UCP_AI_CombatPlane::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);

	InterpPawnSpeed(_DeltaSeconds, PawnMovement_Tick);
	ProcessSpeed(PawnMovement_AnimInst);
}

/*
 * 이 인터페이스 함수는 다른 클래스의 Tick에서 호출되는 것이기에 여기의 PawnMovement 값을 받아서
 * NativeUpdateAnimation에서 애니메이션의 틱에 맞도록 바꿔줘야 한다.
 * 따라서 NativeUpdateAnimation에서 현재 PawnMovement 값을 받고
 * 이것을 타깃 값으로 삼아 NativeUpdateAnimation에서 FInterpTo가 작동하도록 만들고자 한다.
 */
void UCP_AI_CombatPlane::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
	PawnMovement_Tick = _PawnMovement;
}

void UCP_AI_CombatPlane::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void UCP_AI_CombatPlane::InterpPawnSpeed(float _DeltaSeconds, const FPawnMovement& _PawnMovement)
{
	PawnMovement_AnimInst.Speed_Rotation = FMath::RInterpTo(PawnMovement_AnimInst.Speed_Rotation,
		_PawnMovement.Speed_Rotation, _DeltaSeconds, 1.f);
	PawnMovement_AnimInst.Speed_Move = FMath::FInterpTo(PawnMovement_AnimInst.Speed_Move, _PawnMovement.Speed_Move,
		_DeltaSeconds, 1.f);
}

void UCP_AI_CombatPlane::ProcessSpeed(const FPawnMovement& _PawnMovement)
{
	CPLOG(Warning, TEXT(" _PawnMovement.Speed_Rotation : %s"), *_PawnMovement.Speed_Rotation.ToString());
}
