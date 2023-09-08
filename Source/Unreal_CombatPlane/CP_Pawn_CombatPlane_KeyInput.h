// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane_Tick.h"
#include "CP_Pawn_CombatPlane_KeyInput.generated.h"

/**
 * �츮�� CP_Pawn_CombatPlane_Tick���� ����� �޾Ƽ� this�� ����� �ƹ��͵� �߰����� �ʾҴµ� 
 * GM���� this�� Pawn���� �����ϴ� CP_Pawn_CombatPlane_Tick�� ����� �Ȱ��� �����ȴ�.
 * �׷��� �Լ��� ����ؼ� �����ϴ� ���� �˾ƺ���.
 * �ٸ� �ƹ� ���� ���� Ŭ������ ������ ���ϰ� �ϰ� �ڽ� Ŭ������ �����ϵ��� ������ִ� protected�� ������ �˾ƾ� �Ѵ�.
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
