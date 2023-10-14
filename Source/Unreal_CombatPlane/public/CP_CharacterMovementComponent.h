// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CP_Pawn_To_AnimInst.h"
#include "CP_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API UCP_CharacterMovementComponent : public UCharacterMovementComponent, public ICP_Pawn_To_AnimInst
{
	GENERATED_BODY()

public:
	UCP_CharacterMovementComponent(const FObjectInitializer& _ObjectInitializer);

protected:
	// ������Ʈ�� ���Ϳ� �߰��ǰų� ������ ���۵� �� ȣ��. �׿� �޸� �����ڴ� �÷��� �� ������ �󿡼��� ��� �ߵ���.
	virtual void InitializeComponent() override;

	virtual void TickComponent(float _DeltaTime, enum ELevelTick _TickType, FActorComponentTickFunction* _ThisTickFunction) override;
	virtual void SimulateMovement(float DeltaTime) override;

	// �θ� Ŭ�������� ������ ����ִ� �ٵ� ���� �Լ�(�������̽��� �����Լ�ó��!).
	virtual void OnMovementUpdated(float _DeltaSeconds, const FVector& _OldLocation, const FVector& _OldVelocity) override;

private:
	virtual void PropellerTypeTick_Implementation(FPawnMovement _PawnMovement) override;
	virtual void JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement) override;

	UAnimInstance* pAnimInstance;

};
