// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_AI_CombatPlane.h"

// AnimInstance에서의 Tick의 역할을 하는 함수
void UCP_AI_CombatPlane::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);

#pragma region WithoutInterface
	//const auto Pawn = TryGetPawnOwner();
	//if (IsValid(Pawn))
	//{
	//	/*
	//	 * Pawn 클래스 일반에 해당되는 내용이면 Cast 없이 그냥 Pawn에 애로우(->) 써서 접근해도 된다.
	//	 * 하지만 Pawn 클래스의 상속을 받은 우리의 CP_Pawn_AnimInst 클래스에서 선언한 내용이면 형변환을 해줘야 한다.
	//	 */

	//}
#pragma endregion WithoutInterface

#pragma region WithInterface
	InterpPawnSpeed(_DeltaSeconds, PawnMovement_Tick);
	ProcessSpeed(PawnMovement_AnimInst);
#pragma endregion WithInterface
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

/*
 * 다음 함수는 마우스입력으로부터 받은 속도 값을 각도로 변환한다.
 * Aileron은 그 절대값이 최대 40을 가진다고 가정한다.
 * Roll 방향으로 회전하는 것에 대해 양쪽 날개에 더해질 수 있는 각의 절대값은 최대 20도,
 * Pitch 방향으로 회전하는 것에 대해 양쪽 날개에 더해질 수 있는 각의 절대값은 최대 20도라고 해보자.
 * 이를 Clamp로 구현할 수 있다. Aileron의 각도는 그 절대값이 40 미만이다.
 *
 * PawnMovement_AnimInst.Speed_Move는 0에서 5000.f 사이의 값을 가진다.
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
