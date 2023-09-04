// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane_Tick.h"
#include "CP_Pawn_To_AnimInstance.h"
#include "CP_Pawn_CombatPlane_KeyInput.generated.h"

/**
 * �츮�� CP_Pawn_CombatPlane_Tick���� ����� �޾Ƽ� this�� ����� �ƹ��͵� �߰����� �ʾҴµ� 
 * GM���� this�� Pawn���� �����ϴ� CP_Pawn_CombatPlane_Tick�� ����� �Ȱ��� �����ȴ�.
 * �׷��� �Լ��� ����ؼ� �����ϴ� ���� �˾ƺ���.
 * �ٸ� �ƹ� ���� ���� Ŭ������ ������ ���ϰ� �ϰ� �ڽ� Ŭ������ �����ϵ��� ������ִ� protected�� ������ �˾ƾ� �Ѵ�.
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_Pawn_CombatPlane_KeyInput : public ACP_Pawn_CombatPlane_Tick, public ICP_Pawn_To_AnimInstance
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;

private:
	virtual void MoveForwardWithInfPtEnum(float _DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(UInputComponent* _InputComponent) override;

private:
	float AxisSpeed{ 250.f };

	float CurrentSpeed_Roll{ 0.f };
	float CurrentSpeed_Pitch{ 0.f };
	float CurrentSpeed_Yaw{ 0.f };
	
	void ProcessPitch(float _Value);
	void ProcessYaw(float _Value);
	
public:
	virtual void PropellerTypeTick_Implementation() override;
	virtual void JetEngineTypeTick_Implementation() override;

};
