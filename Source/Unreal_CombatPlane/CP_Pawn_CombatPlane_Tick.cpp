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

void ACP_Pawn_CombatPlane_Tick::Tick(float DeltaTime) // 우선 Tick에서 Pawn의 이동을 구현하고 쓰지 않게 되면 함수를 만들어서 빼주자
{
	Super::Tick(DeltaTime);

	MoveForward(DeltaTime);
}

void ACP_Pawn_CombatPlane_Tick::MoveForward(float _DeltaTime) 
{ 
	SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, _DeltaTime * 200.f)); 
}

// 연습: 여기서 일정 고도가 되면 앞으로 가는 것을 구현해 보자.
void ACP_Pawn_CombatPlane_Tick::MoveForwardAfterTakeOff(float _DeltaTime)
{
	if (GetActorLocation().Z < 1000.f)
		SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, _DeltaTime * 7500.f));
	else
		SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, 0.f));
}

// 연습: 그러면, 비행기가 이륙하듯이 앞으로 가면서 뜨도록(2차함수 곡선?) 구현해 보자. 
void ACP_Pawn_CombatPlane_Tick::MoveForwardWhileTakeOff(float _DeltaTime) 
{ 
	SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
}

// 연습: 그리고 Rotation을 통해 발진하는 각도가 변화하도록 연출해 보자... 그리고 X, Y, Z 값에 하나하나 넣어 보면서 감을 잡아보자.
void ACP_Pawn_CombatPlane_Tick::MoveForwardWithCurve(float _DeltaTime)
{
	SetActorLocation(GetActorLocation() + FVector(_DeltaTime * 750.f, 0.f, _DeltaTime * _DeltaTime * 7500.f));
	SetActorRotation(GetActorRotation() + FRotator(_DeltaTime * 5.f, 0.f, 0.f));
}

// 연습: 변곡점을 기준으로 기울기가 변하도록 연출해 보자. flag를 이용한 로직을 배워보도록 한다.
void ACP_Pawn_CombatPlane_Tick::MoveForwardWithInfPt(float _DeltaTime)
{
	if (GetActorRotation().Pitch > 45.f) // 45도 각도를 넘기면 변곡점을 지난 것으로 간주.
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
	if (GetActorRotation().Pitch > 45.f) // 45도 각도를 넘기면 변곡점을 지난 것으로 간주.
		CurrentState = EPlaneState::AFTER_45;
	else if (GetActorRotation().Pitch < 0.f && CurrentState == EPlaneState::AFTER_45) // 한번 45도 각도를 넘겼는데 다시 0도에 도달하면 세번째 상태로 설정한다.
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

