// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_AI_CombatPlane.h"

UCP_AI_CombatPlane::UCP_AI_CombatPlane()
{
}

// AnimInstance������ Tick�� ������ �ϴ� �Լ�
void UCP_AI_CombatPlane::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);

	InterpPawnSpeed(_DeltaSeconds, PawnMovement_Tick);
	CPLOG(Warning, TEXT(" Speed_Rotation.Roll : %f, Speed_Move : %f"), PawnMovement_AnimInst.Speed_Rotation.Roll, PawnMovement_AnimInst.Speed_Move);
}

/*
 * �� �������̽� �Լ��� �ٸ� Ŭ������ Tick���� ȣ��Ǵ� ���̱⿡ ������ PawnMovement ���� �޾Ƽ�
 * NativeUpdateAnimation���� �ִϸ��̼��� ƽ�� �µ��� �ٲ���� �Ѵ�.
 * ���� NativeUpdateAnimation���� ���� PawnMovement ���� �ް�
 * �̰��� Ÿ�� ������ ��� NativeUpdateAnimation���� FInterpTo�� �۵��ϵ��� ������� �Ѵ�.
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
	PawnMovement_AnimInst.Speed_Rotation.Roll = FMath::FInterpTo(PawnMovement_AnimInst.Speed_Rotation.Roll, _PawnMovement.Speed_Rotation.Roll, _DeltaSeconds, 1.f);
	PawnMovement_AnimInst.Speed_Move = FMath::FInterpTo(PawnMovement_AnimInst.Speed_Move, _PawnMovement.Speed_Move, _DeltaSeconds, 1.f);
}

void UCP_AI_CombatPlane::AddLocalMove()
{
}
