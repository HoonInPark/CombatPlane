// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_AnimInst.h"
#include "CP_AI_CombatPlane.h"

ACP_Pawn_AnimInst::ACP_Pawn_AnimInst()
{
	pAnimInstance = nullptr;

	/*
	// ���1 : �ִ� ������ ���� ����
	pBodyMeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> COMBATPLANE_ANIM(TEXT("/Game/_01_BasicSettings/Animations/ABP_CombatPlane.ABP_CombatPlane_C"));
	if (COMBATPLANE_ANIM.Succeeded())
	{
		pBodyMeshComp->SetAnimInstanceClass(COMBATPLANE_ANIM.Class);
	}
	*/
}

void ACP_Pawn_AnimInst::BeginPlay()
{
	Super::BeginPlay();

}

void ACP_Pawn_AnimInst::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*
	 * �츮�� ���⼭ �÷��� ���۰� ���ÿ� ���� ���ӵ��� �ٿ��� �̷��ϵ��� ������� ���ε�,
	 * ���� ACP_Pawn_CombatPlane_KeyInput Ŭ�������� �̷� ���ӱ���� �� ���� �ʴ�.
	 * ���� ACP_Pawn_CombatPlane_KeyInput Ŭ������ LocalMove_X ������ �������̵����� ���̴�.
	 * ���⼭ Ư�� ��ü�� ��ȣ�� ������ �ϴµ�, �ܼ��� Ŭ������ �̸��� �˾Ƽ��� �ȵǰ�,
	 * ��ü������ ��� ��üȭ�� ������ ����ؾ� �Ѵ�.
	 * �׸��� �ٷ� ���� �μ��δ� ���� �� �Լ��� �޴� �Ű������� ��Ÿ����.
	 * �� �μ��� ���� �ٸ� Ŭ������ ���� ���� �� �ִ�.
	 */
	const FPawnMovement PawnMovement = { DeltaRotation, AddLocalMove(DeltaTime) }; // �� �� ���ӵ��̴�!
	pAnimInstance = pBodyMeshComp->GetAnimInstance();

	ICP_Pawn_To_AnimInst::Execute_PropellerTypeTick(
		pAnimInstance, PawnMovement
	);
}

void ACP_Pawn_AnimInst::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Pawn_AnimInst::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

float ACP_Pawn_AnimInst::AddLocalMove(float _DeltaTime) 
{
	LocalMove_Delta = FMath::FInterpTo(LocalMove_Delta, 10000.f, _DeltaTime, 0.25f);
	const FVector LocalMove_AnimInst = FVector(_DeltaTime * LocalMove_Delta, 0.f, 0.f);
	AddActorLocalOffset(LocalMove_AnimInst);

	return LocalMove_AnimInst.X;
}
