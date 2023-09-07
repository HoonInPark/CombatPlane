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

FPawnMovement UCP_AI_CombatPlane::PropellerTypeTick_Implementation()
{
	FPawnMovement test = { FRotator::ZeroRotator, 0.f };
	return test;
}

FPawnMovement UCP_AI_CombatPlane::JetEngineTypeTick_Implementation()
{
	FPawnMovement test = { FRotator::ZeroRotator, 0.f };
	return test;
}
	