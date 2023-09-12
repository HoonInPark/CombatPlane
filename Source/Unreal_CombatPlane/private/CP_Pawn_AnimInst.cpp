// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_AnimInst.h"
#include "CP_AI_CombatPlane.h"

ACP_Pawn_AnimInst::ACP_Pawn_AnimInst()
{
	pAnimInstance = nullptr;
}

/*
 * ������Ʈ�� ��� �ε�ǰ� �ش� Ŭ������ ��� �������� �ʱ�ȭ�� ���Ŀ� ȣ��Ǵ� �Լ��̴�.
 * �׷��� BeginPlay() ���� �̹� ������� ������Ʈ�� �����ؾ��� �� �����ϴ�.
 */
void ACP_Pawn_AnimInst::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UAnimInstance* CurrentAnimInstance = pBodyMeshComp->GetAnimInstance();

	if (!CurrentAnimInstance)
	{
		pAnimInstance = NewObject<UCP_AI_CombatPlane>(pBodyMeshComp,
		                                              UCP_AI_CombatPlane::StaticClass());
		pBodyMeshComp->SetAnimInstanceClass(pAnimInstance->GetClass());
		CPLOG_S(Warning);
	}
	else
	{
		pAnimInstance = Cast<UCP_AI_CombatPlane>(CurrentAnimInstance);
		//CPLOG_S(Warning);
		CPLOG(Warning, TEXT(" pAnimInstance : %s"), *pAnimInstance->GetName());
		// Unreal_CombatPlane: Warning: ACP_Pawn_AnimInst::PostInitializeComponents(30) pAnimInstance : ABP_CombatPlane_C_0
	}
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
	 * ��ü������ ��� ��üȭ�� ������ �����ؾ� �Ѵ�.
	 * �׸��� �ٷ� ���� �μ��δ� ���� �� �Լ��� �޴� �Ű������� ��Ÿ����.
	 * �� �μ��� ���� �ٸ� Ŭ������ ���� ���� �� �ִ�.
	 */
	const FPawnMovement PawnMovement = {DeltaRotation, AddLocalMove(DeltaTime)}; // �� �� ���ӵ��̴�!
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