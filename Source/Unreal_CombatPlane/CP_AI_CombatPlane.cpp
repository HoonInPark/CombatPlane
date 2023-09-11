// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_AI_CombatPlane.h"

// AnimInstance������ Tick�� ������ �ϴ� �Լ�
void UCP_AI_CombatPlane::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);

	InterpPawnSpeed(_DeltaSeconds, PawnMovement_Tick);
	ProcessSpeed(PawnMovement_AnimInst);
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
	PawnMovement_AnimInst.Speed_Rotation = FMath::RInterpTo(PawnMovement_AnimInst.Speed_Rotation,
		_PawnMovement.Speed_Rotation, _DeltaSeconds, 1.f);
	PawnMovement_AnimInst.Speed_Move = FMath::FInterpTo(PawnMovement_AnimInst.Speed_Move, _PawnMovement.Speed_Move,
		_DeltaSeconds, 1.f);
}

/*
 * Aileron�� �� ���밪�� �ִ� 40�� �����ٰ� �����Ѵ�.
 * Roll �������� ȸ���ϴ� �Ϳ� ���� ���� ������ ������ �� �ִ� ���� ���밪�� �ִ� 20��,
 * Pitch �������� ȸ���ϴ� �Ϳ� ���� ���� ������ ������ �� �ִ� ���� ���밪�� �ִ� 20����� �غ���.
 * �̸� Clamp�� ������ �� �ִ�. Aileron�� ������ �� ���밪�� 40 �̸��̴�.
 */
void UCP_AI_CombatPlane::ProcessSpeed(const FPawnMovement& _PawnMovement)
{
	CPLOG(Warning, TEXT(" _PawnMovement.Speed_Rotation : %s"), *_PawnMovement.Speed_Rotation.ToString());
 
	// roll�� ����� ����(���������� ������ Ʋ ��)�ϰų� Pitch�� ����� ����(���� ������ Ʋ ��)�� �� Aileron_rt�� ���� �����Ѵ�.
	Aileron_rt = FMath::Clamp(-20.f * _PawnMovement.Speed_Rotation.Roll - 20.f * _PawnMovement.Speed_Rotation.Pitch, -40.f, 40.f);
	// roll�� ������ ����(�������� ������ Ʋ ��)�ϰų� Pitch�� ����� ����(���� ������ Ʋ ��)�� �� Aileron_rt�� ���� �����Ѵ�.
	Aileron_lf = FMath::Clamp(20.f * _PawnMovement.Speed_Rotation.Roll - 20.f * _PawnMovement.Speed_Rotation.Pitch, -40.f, 40.f);;
	
}
