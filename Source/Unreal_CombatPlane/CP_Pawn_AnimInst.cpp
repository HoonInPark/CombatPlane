// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_AnimInst.h"
#include "CP_AI_CombatPlane.h"

ACP_Pawn_AnimInst::ACP_Pawn_AnimInst()
{
	pAnimInstance = nullptr;
}

void ACP_Pawn_AnimInst::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAnimInstance* CurrentAnimInstance = pBodyMeshComp->GetAnimInstance();

	if (!CurrentAnimInstance)
	{
		pAnimInstance = NewObject<UCP_AI_CombatPlane>(pBodyMeshComp,
		                                              UCP_AI_CombatPlane::StaticClass());
		pBodyMeshComp->SetAnimInstanceClass(pAnimInstance->GetClass());
	}
	else
		pAnimInstance = Cast<UCP_AI_CombatPlane>(CurrentAnimInstance);
}

void ACP_Pawn_AnimInst::BeginPlay()
{
	Super::BeginPlay();
}

void ACP_Pawn_AnimInst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	 * 우리는 여기서 플레이 시작과 동시에 점점 가속도를 붙여서 이륙하도록 만들어줄 것인데,
	 * 기존 ACP_Pawn_CombatPlane_KeyInput 클래스에는 이런 가속기능이 들어가 있지 않다.
	 * 따라서 ACP_Pawn_CombatPlane_KeyInput 클래스의 LocalMove_X 변수를 오버라이드해줄 것이다.
	 */
	AddLocalMove(DeltaTime);

	// 여기서 특정 객체에 신호를 보내야 하는데, 단순히 클래스의 이름만 알아서는 안되고, 구체적으로 어디에 객체화된 것인지 명시해야 한다.
	ICP_Pawn_To_AnimInst::Execute_PropellerTypeTick(
		pAnimInstance,
		{DeltaRotation, LocalMove_X});
}

void ACP_Pawn_AnimInst::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Pawn_AnimInst::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Pawn_AnimInst::AddLocalMove(float _DeltaTime)
{
	LocalMove_X = FMath::FInterpTo(LocalMove_X, 10000.f, _DeltaTime, 0.25f);
	const FVector LocalMove_AnimInst = FVector(_DeltaTime * LocalMove_X, 0.f, 0.f);
	AddActorLocalOffset(LocalMove_AnimInst);
}
