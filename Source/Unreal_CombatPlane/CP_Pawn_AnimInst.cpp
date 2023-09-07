// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_AnimInst.h"

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

}

FPawnMovement ACP_Pawn_AnimInst::PropellerTypeTick_Implementation()
{
	FPawnMovement test = { FRotator::ZeroRotator, 0.f };
	return test;
}

FPawnMovement ACP_Pawn_AnimInst::JetEngineTypeTick_Implementation()
{
	FPawnMovement test = { FRotator::ZeroRotator, 0.f };
	return test;
}
