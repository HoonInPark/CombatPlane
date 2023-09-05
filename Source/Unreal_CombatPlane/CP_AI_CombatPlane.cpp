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

// 프로펠러를 돌리는 함수
void UCP_AI_CombatPlane::SpinPropeller()
{
}

// 수평 방향을 잡는 날개의 각도를 변형해 주는 함수
void UCP_AI_CombatPlane::MoveAileron()
{
}

void UCP_AI_CombatPlane::PropellerTypeTick_Implementation()
{
}

void UCP_AI_CombatPlane::JetEngineTypeTick_Implementation()
{
}
