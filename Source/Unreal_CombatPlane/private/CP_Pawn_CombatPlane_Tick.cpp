// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_CombatPlane_Tick.h"


ACP_Pawn_CombatPlane_Tick::ACP_Pawn_CombatPlane_Tick() 
{ 
	Flag_InfPt = 0;
}

void ACP_Pawn_CombatPlane_Tick::BeginPlay() 
{ 
	Super::BeginPlay(); 

}

void ACP_Pawn_CombatPlane_Tick::Tick(float DeltaTime) // �켱 Tick���� Pawn�� �̵��� �����ϰ� ���� �ʰ� �Ǹ� �Լ��� ���� ������
{
	Super::Tick(DeltaTime);

	MoveForward(DeltaTime);
}

void ACP_Pawn_CombatPlane_Tick::MoveForward(float _DeltaTime) 
{ 
	SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, _DeltaTime * 200.f)); 
}

// ����: ���⼭ ���� ���� �Ǹ� ������ ���� ���� ������ ����.
void ACP_Pawn_CombatPlane_Tick::MoveForwardAfterTakeOff(float _DeltaTime)
{
	if (GetActorLocation().Z < 1000.f)
		SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, _DeltaTime * 7500.f));
	else
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, 0.f));
}

// ����: �׷���, ����Ⱑ �̷��ϵ��� ������ ���鼭 �ߵ���(2���Լ� �?) ������ ����. 
void ACP_Pawn_CombatPlane_Tick::MoveForwardWhileTakeOff(float _DeltaTime) 
{ 
	SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
}

// ����: �׸��� Rotation�� ���� �����ϴ� ������ ��ȭ�ϵ��� ������ ����... �׸��� X, Y, Z ���� �ϳ��ϳ� �־� ���鼭 ���� ��ƺ���.
void ACP_Pawn_CombatPlane_Tick::MoveForwardWithCurve(float _DeltaTime)
{
	SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
	SetActorRotation(GetActorRotation() + FRotator(_DeltaTime * 5.f, 0.f, 0.f));
}

// ����: �������� �������� ���Ⱑ ���ϵ��� ������ ����. flag�� �̿��� ������ ��������� �Ѵ�.
void ACP_Pawn_CombatPlane_Tick::MoveForwardWithInfPt(float _DeltaTime)
{
	if (GetActorRotation().Pitch > 45.f) // 45�� ������ �ѱ�� �������� ���� ������ ����.
		Flag_InfPt = 1;
	else if (GetActorRotation().Pitch < 0.f && Flag_InfPt == 1)
		Flag_InfPt = 2;
	
	switch (Flag_InfPt)
	{
	case 0:
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
		SetActorRotation(GetActorRotation() + FRotator(_DeltaTime * 5.f, 0.f, 0.f));
		break;
	case 1:
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
		SetActorRotation(GetActorRotation() - FRotator(_DeltaTime * 5.f, 0.f, 0.f));
		break;
	case 2:
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, 0.f));
		break;
	default:
		break;
	}
}

void ACP_Pawn_CombatPlane_Tick::MoveForwardWithInfPtEnum(float _DeltaTime)
{
	if (GetActorRotation().Pitch > 45.f) // 45�� ������ �ѱ�� �������� ���� ������ ����.
		CurrentState = EPlaneState::AFTER_45;
	else if (GetActorRotation().Pitch < 0.f && CurrentState == EPlaneState::AFTER_45) // �ѹ� 45�� ������ �Ѱ�µ� �ٽ� 0���� �����ϸ� ����° ���·� �����Ѵ�.
		CurrentState = EPlaneState::AFTER_0;

	switch (CurrentState)
	{
	case EPlaneState::BEFORE_45:
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
		SetActorRotation(GetActorRotation() + FRotator(_DeltaTime * 5.f, 0.f, 0.f));
		break;
	case EPlaneState::AFTER_45:
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
		SetActorRotation(GetActorRotation() - FRotator(_DeltaTime * 5.f, 0.f, 0.f));
		break;
	case EPlaneState::AFTER_0:
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, 0.f));
		break;
	}
}

