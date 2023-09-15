// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_AI_CombatPlane.h"

// AnimInstance������ Tick�� ������ �ϴ� �Լ�
void UCP_AI_CombatPlane::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);

#pragma region WithoutInterface
	//const auto Pawn = TryGetPawnOwner();
	//if (IsValid(Pawn))
	//{
	//	/*
	//	 * Pawn Ŭ���� �Ϲݿ� �ش�Ǵ� �����̸� Cast ���� �׳� Pawn�� �ַο�(->) �Ἥ �����ص� �ȴ�.
	//	 * ������ Pawn Ŭ������ ����� ���� �츮�� CP_Pawn_AnimInst Ŭ�������� ������ �����̸� ����ȯ�� ����� �Ѵ�.
	//	 */

	//}
#pragma endregion WithoutInterface

#pragma region WithInterface
	InterpPawnSpeed(_DeltaSeconds, PawnMovement_Tick);
	ProcessSpeed(PawnMovement_AnimInst);
#pragma endregion WithInterface
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
 * ���� �Լ��� ���콺�Է����κ��� ���� �ӵ� ���� ������ ��ȯ�Ѵ�.
 * Aileron�� �� ���밪�� �ִ� 40�� �����ٰ� �����Ѵ�.
 * Roll �������� ȸ���ϴ� �Ϳ� ���� ���� ������ ������ �� �ִ� ���� ���밪�� �ִ� 20��,
 * Pitch �������� ȸ���ϴ� �Ϳ� ���� ���� ������ ������ �� �ִ� ���� ���밪�� �ִ� 20����� �غ���.
 * �̸� Clamp�� ������ �� �ִ�. Aileron�� ������ �� ���밪�� 40 �̸��̴�.
 *
 * PawnMovement_AnimInst.Speed_Move�� 0���� 5000.f ������ ���� ������.
 */
void UCP_AI_CombatPlane::ProcessSpeed(const FPawnMovement& _PawnMovement)
{
	//CPLOG(Warning, TEXT(" _PawnMovement.Speed_Rotation : %s"), *_PawnMovement.Speed_Rotation.ToString());
 
	Aileron_rt = FMath::Clamp(-40.f * _PawnMovement.Speed_Rotation.Roll - 40.f, -40.f, 40.f);
	Aileron_lf = FMath::Clamp(40.f * _PawnMovement.Speed_Rotation.Roll - 40.f, -40.f, 40.f);

	Elevator = FMath::Clamp(-40.f * _PawnMovement.Speed_Rotation.Pitch, -40.f, 40.f);

	Rudder = FMath::Clamp(-40.f * _PawnMovement.Speed_Rotation.Yaw, -40.f, 40.f);
	
	if (Propeller < 360.f)
		Propeller += PawnMovement_AnimInst.Speed_Move / 100.f * 360.f;
	else
		Propeller += -360.f + PawnMovement_AnimInst.Speed_Move / 100.f * 360.f;
}
