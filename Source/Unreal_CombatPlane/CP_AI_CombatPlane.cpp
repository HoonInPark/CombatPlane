// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_AI_CombatPlane.h"

UCP_AI_CombatPlane::UCP_AI_CombatPlane()
{
}

// AnimInstance에서의 Tick의 역할을 하는 함수
void UCP_AI_CombatPlane::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);

}

void UCP_AI_CombatPlane::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
	CPLOG(Warning, TEXT(" _PawnMovement.Speed_Move : %f"), _PawnMovement.Speed_Move);
	CPLOG(Warning, TEXT(" _PawnMovement.Speed_Rotation : %s"), *_PawnMovement.Speed_Rotation.ToString());


}

void UCP_AI_CombatPlane::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}