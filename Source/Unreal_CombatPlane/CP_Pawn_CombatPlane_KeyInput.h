// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane_Tick.h"
#include "CP_Pawn_CombatPlane_KeyInput.generated.h"

/**
 * 우리는 CP_Pawn_CombatPlane_Tick에서 상속을 받아서 this를 만들고 아무것도 추가하지 않았는데 
 * GM에서 this를 Pawn으로 설정하니 CP_Pawn_CombatPlane_Tick의 기능이 똑같이 구현된다.
 * 그러면 함수를 상속해서 변경하는 법도 알아보자.
 * 다른 아무 관련 없는 클래스는 접근을 못하게 하고 자식 클래스만 접근하도록 만들어주는 protected의 사용법을 알아야 한다.
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_Pawn_CombatPlane_KeyInput : public ACP_Pawn_CombatPlane_Tick
{
	GENERATED_BODY()

public:
	ACP_Pawn_CombatPlane_KeyInput();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	virtual void MoveForwardWithInfPtEnum(float _DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* _InputComponent) override;

private:
	const float AxisSpeed{ 250.f };

	float CurrentSpeed_Roll{ 0.f };
	float CurrentSpeed_Pitch{ 0.f };
	float CurrentSpeed_Yaw{ 0.f };
	
	void ProcessPitch(float _Value);
	void ProcessYaw(float _Value);

	float StabilizeRoll(float _DeltaTime);
	
	const FRotator DefaultSpringArmRotation{ FRotator(-15.f, 0.f, 0.f) };
	void StabilizeSpringArm(float _DeltaTime) const;
	
public:
	UPROPERTY()
	USpringArmComponent* pSpringArm;

protected:
	FRotator DeltaRotation{ FRotator::ZeroRotator };
	float LocalMove_X{ 0.f };
	virtual void AddLocalMove(float _DeltaTime);
};
