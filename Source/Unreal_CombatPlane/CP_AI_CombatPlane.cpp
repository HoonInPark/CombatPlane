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

/*
 * Aileron은 그 절대값이 최대 40을 가진다고 가정한다.
 * Roll 방향으로 회전하는 것에 대해 양쪽 날개에 더해질 수 있는 각의 절대값은 최대 20도,
 * Pitch 방향으로 회전하는 것에 대해 양쪽 날개에 더해질 수 있는 각의 절대값은 최대 20도라고 해보자.
 * 이를 Clamp로 구현할 수 있다. Aileron의 각도는 그 절대값이 40 미만이다.
 */
void UCP_AI_CombatPlane::ProcessSpeed(const FPawnMovement& _PawnMovement)
{
	CPLOG(Warning, TEXT(" _PawnMovement.Speed_Rotation : %s"), *_PawnMovement.Speed_Rotation.ToString());
 
	// roll이 양수로 증가(오른쪽으로 방향을 틀 때)하거나 Pitch가 양수로 증가(위로 방향을 틀 때)할 때 Aileron_rt의 값이 감소한다.
	Aileron_rt = FMath::Clamp(-20.f * _PawnMovement.Speed_Rotation.Roll - 20.f * _PawnMovement.Speed_Rotation.Pitch, -40.f, 40.f);
	// roll이 음수로 감소(왼쪽으로 방향을 틀 때)하거나 Pitch가 양수로 증가(위로 방향을 틀 때)할 때 Aileron_rt의 값이 감소한다.
	Aileron_lf = FMath::Clamp(20.f * _PawnMovement.Speed_Rotation.Roll - 20.f * _PawnMovement.Speed_Rotation.Pitch, -40.f, 40.f);;
	
}
