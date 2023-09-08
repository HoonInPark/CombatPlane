// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_AnimInst.h"

#include "CP_AI_CombatPlane.h"

ACP_Pawn_AnimInst::ACP_Pawn_AnimInst()
{
}

void ACP_Pawn_AnimInst::BeginPlay()
{
	Super::BeginPlay();
}

void ACP_Pawn_AnimInst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ICP_Pawn_To_AnimInst::Execute_PropellerTypeTick(
		UGameplayStatics::GetActorOfClass(GetWorld(), UCP_AI_CombatPlane::StaticClass()),
		{DeltaRotation, 0.f/*이동 속도 값 넣어준다.*/});
}

void ACP_Pawn_AnimInst::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Pawn_AnimInst::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}
