// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_CombatPlane_KeyInput.h"

void ACP_Pawn_CombatPlane_KeyInput::BeginPlay()
{
	Super::BeginPlay();

	// ������ ���� �α׸� �� �θ� Ŭ������ ������ �� ����� �ƴ��� Ȯ���� �� �ִ�.
	CPLOG(Warning, TEXT(" Inherited Value of CurrrentState is %d"), CurrrentState);
}

void ACP_Pawn_CombatPlane_KeyInput::Tick(float DeltaTime)
{
	//CPLOG(Warning, TEXT(" DeltaTime is %f"), DeltaTime);
	//MoveForwardWithInfPtEnum(DeltaTime);
	
// �ε巴�� �����̴� �� ���� ��ٷ� ���Է��� �Դ� �ڵ�
#pragma region AxisMapping
	/*
	const FVector LocalMove = FVector(DeltaTime * 1000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * DeltaTime; // ��/�Ʒ�!
	DeltaRotation.Yaw = CurrentSpeed_Yaw * DeltaTime; // �� ��!

	AddActorLocalRotation(DeltaRotation);
	*/
#pragma endregion AxisMapping
	
// �ε巴�� ȸ���ϵ��� InterpTo�� ����ϴ� �ڵ�
#pragma region InterpAxisMapping 
	const FVector LocalMove = FVector(DeltaTime * 5000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * DeltaTime; // ��/�Ʒ�!
	DeltaRotation.Yaw = CurrentSpeed_Yaw * DeltaTime; // �� ��!

// Roll ���� ������ ������ �ִ� �ڵ�
#pragma region MaintainPlane
	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, DeltaTime, 2.f);
	DeltaRotation.Roll = CurrentSpeed_Roll * DeltaTime;
#pragma endregion MaintainPlane

	AddActorLocalRotation(DeltaRotation);
#pragma endregion InterpAxisMapping
	
	if (DeltaRotation.Pitch > 100.f)
	{
		CPLOG(Warning, TEXT("Rotation Spark Evoked in : %s"), *GetActorRotation().ToString());
	}
}

// �̷��� �������̵��� �Լ��� �����ϸ� �θ�Ŭ������ ������ �� �Լ��� ����� �ڽ� Ŭ���������� �۵����� �ʴ´�. �α� ��ų� ������� ���� �� �� �ִ�.
void ACP_Pawn_CombatPlane_KeyInput::MoveForwardWithInfPtEnum(float _DeltaTime)
{
	// �ٸ� ������ ���� �θ� Ŭ������ ����(EPlaneState)�� �����ؼ� �θ� Ŭ������ ��ɰ��� �ٸ� �Լ��� ���� �� �ִ�.
	
	if (GetActorRotation().Pitch > 45.f) 
	{
		CurrrentState = EPlaneState::AFTER_45;
		// ���� �θ� Ŭ������ MoveForwardWithInfPtEnum�� �۵��ߴ��� �ƴϸ� �ڽ� Ŭ������ MoveForwardWithInfPtEnum�� �۵��ߴ��� Ȯ���� ������ �α׸� ����.
		CPLOG(Warning, TEXT("CurrrentState has changed to %d in overrided function"), CurrrentState);
	}
	else if (GetActorRotation().Pitch < 0.f && CurrrentState == EPlaneState::AFTER_45)
	{
		CurrrentState = EPlaneState::AFTER_0;
		CPLOG(Warning, TEXT("CurrrentState has changed to %d in overrided function"), CurrrentState);
	}

	switch (CurrrentState)
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
	
	// �������̵��� �� �ǰ� �ִ��� ������� Ȯ���� ������ �߰��غô�.
	SetActorRotation(GetActorRotation() + FRotator(0.f, 0.f, _DeltaTime * 100.f)); 
}

#pragma region AxisMapping
// ���⼭ ���콺�κ��� ���Է��� ���� ����.
void ACP_Pawn_CombatPlane_KeyInput::SetupPlayerInputComponent(UInputComponent* _InputComponent)
{
	_InputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Pawn_CombatPlane_KeyInput::ProcessPitch); // delegate!
	_InputComponent->BindAxis(TEXT("TurnAround"), this, &ACP_Pawn_CombatPlane_KeyInput::ProcessYaw); 
}

/*
* ����ο��� �������ִ� _Value ���� ���밪�� 0�� 1 ������ �Ǽ��̴�. ���콺�� �������� �������� �̰��� ���밪�� 1�� ���������.
* DeltaTime�� ���� ������ ���� �ð������̴�. ������ ���̴�.
* �α׸� ���� �˰�����, 60������ ������ ��ǻ�Ϳ��� DeltaTime�� 0.0167�� ���� �ȴ�.
* 
* �츮�� ���콺�� ��� ��� Yaw, Pitch�� ��ȯ�� �ִ� �۾��� �� ���̴�.
* ���콺�� ȭ�� �󿡼��� x ��� ���� ������ ����(Yaw)���� ��ȯ�� �ְ�,
* ���콺�� ȭ�� �󿡼��� y ��� ���� �����̴� ����(Pitch)���� ��ȯ�� �ش�.

void ACP_Pawn_CombatPlane_KeyInput::ProcessPitch(float _Value)
{
	// ������ ���� �α׷� ���콺 ���Է��� ����͸��� �� �ִ�.
	CPLOG(Warning, TEXT(" MouseY Input : %f"), _Value);

	const float TargetSpeedPitch = _Value * AxisSpeed;
	CurrentSpeed_Pitch = TargetSpeedPitch;
}

void ACP_Pawn_CombatPlane_KeyInput::ProcessYaw(float _Value)
{
	CPLOG(Warning, TEXT("   MouseX Input : %f"), _Value);

	const float TargetSpeedYaw = _Value * AxisSpeed;
	CurrentSpeed_Yaw = TargetSpeedYaw;
}
*/

#pragma region InterpAxisMapping
void ACP_Pawn_CombatPlane_KeyInput::ProcessPitch(float _Value)
{
	const float TargetSpeed_Pitch = _Value * AxisSpeed;
	CurrentSpeed_Pitch = FMath::FInterpTo(CurrentSpeed_Pitch, TargetSpeed_Pitch, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ACP_Pawn_CombatPlane_KeyInput::ProcessYaw(float _Value)
{
	const float TargetSpeed_Yaw = _Value * AxisSpeed;
	CurrentSpeed_Yaw = FMath::FInterpTo(CurrentSpeed_Yaw, TargetSpeed_Yaw, GetWorld()->GetDeltaSeconds(), 2.f);
	
	const float TargetSpeed_Roll = _Value * AxisSpeed;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, GetWorld()->GetDeltaSeconds(), 1.f);
	
}
#pragma endregion InterpAxisMapping
#pragma endregion AxisMapping
