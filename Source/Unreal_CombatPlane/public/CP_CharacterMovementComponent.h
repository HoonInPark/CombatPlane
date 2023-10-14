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
	// 컴포넌트가 액터에 추가되거나 게임이 시작될 때 호출. 그와 달리 생성자는 플레이 전 에디터 상에서도 몇번 발동함.
	virtual void InitializeComponent() override;

	virtual void TickComponent(float _DeltaTime, enum ELevelTick _TickType, FActorComponentTickFunction* _ThisTickFunction) override;
	virtual void SimulateMovement(float DeltaTime) override;

	// 부모 클래스에선 완전히 비어있는 바디를 가진 함수(인터페이스의 가상함수처럼!).
	virtual void OnMovementUpdated(float _DeltaSeconds, const FVector& _OldLocation, const FVector& _OldVelocity) override;

private:
	virtual void PropellerTypeTick_Implementation(FPawnMovement _PawnMovement) override;
	virtual void JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement) override;

	UAnimInstance* pAnimInstance;

};
