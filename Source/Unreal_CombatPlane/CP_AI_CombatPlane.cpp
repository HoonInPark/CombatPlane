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

void UCP_AI_CombatPlane::PropellerTypeTick_Implementation()
{
	//ICP_Pawn_To_AnimInst::Execute_PropellerTypeTick(Pawn);
}

void UCP_AI_CombatPlane::JetEngineTypeTick_Implementation()
{
}
