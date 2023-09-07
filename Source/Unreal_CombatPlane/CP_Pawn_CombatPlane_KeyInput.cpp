// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_CombatPlane_KeyInput.h"

ACP_Pawn_CombatPlane_KeyInput::ACP_Pawn_CombatPlane_KeyInput()
{
	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));

	pSpringArm->SetupAttachment(pBodyMeshComp);
	pCamera->SetupAttachment(pSpringArm);
	pCamera->SetRelativeLocation(FVector::ZeroVector);

	pSpringArm->TargetArmLength = 1000.f;
	pSpringArm->SetRelativeLocationAndRotation(FVector(0.f, 0.f, 150.f), DefaultSpringArmRotation);
}

void ACP_Pawn_CombatPlane_KeyInput::BeginPlay()
{
	Super::BeginPlay();

	// 다음과 같이 로그를 찍어서 부모 클래스의 변수가 잘 상속이 됐는지 확인할 수 있다.
	CPLOG(Warning, TEXT(" Inherited Value of CurrrentState is %d"), CurrrentState);
}

void ACP_Pawn_CombatPlane_KeyInput::Tick(float DeltaTime)
{
	//CPLOG(Warning, TEXT(" DeltaTime is %f"), DeltaTime);
	//MoveForwardWithInfPtEnum(DeltaTime);
	
// 부드럽게 움직이는 거 없이 곧바로 축입력을 먹는 코드
#pragma region AxisMapping
	/*
	const FVector LocalMove = FVector(DeltaTime * 1000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * DeltaTime; // 위/아래!
	DeltaRotation.Yaw = CurrentSpeed_Yaw * DeltaTime; // 양 옆!

	AddActorLocalRotation(DeltaRotation);
	*/
#pragma endregion AxisMapping
	
// 부드럽게 회전하도록 InterpTo를 사용하는 코드
#pragma region InterpAxisMapping 
	const FVector LocalMove = FVector(DeltaTime * 5000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * DeltaTime; // 끄덕끄덕
	DeltaRotation.Yaw = CurrentSpeed_Yaw * DeltaTime; // 도리도리
	DeltaRotation.Roll = StabilizeRoll(DeltaTime); // 갸우뚱 

	AddActorLocalRotation(DeltaRotation);
#pragma endregion InterpAxisMapping
	
	pSpringArm->AddLocalRotation(0.1f * DeltaRotation.GetInverse());
	StabilizeSpringArm(DeltaTime);
	
}

// 이렇게 오버라이드한 함수를 정의하면 부모클래스가 구현한 이 함수의 기능은 자식 클래스에서는 작동하지 않는다. 로그 찍거나 디버깅해 보면 알 수 있다.
void ACP_Pawn_CombatPlane_KeyInput::MoveForwardWithInfPtEnum(float _DeltaTime)
{
	// 다만 다음과 같이 부모 클래스의 변수(EPlaneState)에 접근해서 부모 클래스의 기능과는 다른 함수를 만들 수 있다.
	
	if (GetActorRotation().Pitch > 45.f) 
	{
		CurrrentState = EPlaneState::AFTER_45;
		// 과연 부모 클래스의 MoveForwardWithInfPtEnum가 작동했는지 아니면 자식 클래스의 MoveForwardWithInfPtEnum가 작동했는지 확인해 보고자 로그를 찍자.
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
	
	// 오버라이딩이 잘 되고 있는지 기능으로 확인해 보고자 추가해봤다.
	SetActorRotation(GetActorRotation() + FRotator(0.f, 0.f, _DeltaTime * 100.f)); 
}

#pragma region AxisMapping
// 여기서 마우스로부터 축입력을 받을 것임.
void ACP_Pawn_CombatPlane_KeyInput::SetupPlayerInputComponent(UInputComponent* _InputComponent)
{
	Super::SetupPlayerInputComponent(_InputComponent);

	_InputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Pawn_CombatPlane_KeyInput::ProcessPitch); // delegate!
	_InputComponent->BindAxis(TEXT("TurnAround"), this, &ACP_Pawn_CombatPlane_KeyInput::ProcessYaw); 
}

/*
* 축매핑에서 전달해주는 _Value 값은 절대값이 0과 1 사이인 실수이다. 마우스의 움직임이 빠를수록 이것의 절대값은 1에 가까워진다.
* DeltaTime의 값은 프레임 간의 시간간격이다. 단위는 초이다.
* 로그를 찍어보면 알겠지만, 60프레임 성능의 컴퓨터에서 DeltaTime은 0.0167초 정도 된다.
* 
* 우리는 마우스의 평면 운동을 Yaw, Pitch로 변환해 주는 작업을 할 것이다.
* 마우스의 화면 상에서의 x 운돟을 고개를 돌리는 방향(Yaw)으로 변환해 주고,
* 마우스의 화면 상에서의 y 운돟을 고개를 끄덕이는 방향(Pitch)으로 변환해 준다.

void ACP_Pawn_CombatPlane_KeyInput::ProcessPitch(float _Value)
{
	// 다음과 같이 로그로 마우스 축입력을 모니터링할 수 있다.
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
	
	// 고개를 갸우뚱하는 방향으로 회전시켜준다.
	const float TargetSpeed_Roll = _Value * AxisSpeed;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, GetWorld()->GetDeltaSeconds(), 2.f);
	
}
#pragma endregion InterpAxisMapping
#pragma endregion AxisMapping

#pragma region StabilizeArea
// Roll 축의 수평을 유지해 주는 함수
float ACP_Pawn_CombatPlane_KeyInput::StabilizeRoll(float _DeltaTime)
{
	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, _DeltaTime, 2.f);

	return CurrentSpeed_Roll * _DeltaTime;
}

// 여기 _DeltaRotation은 움직이는 각도에 반대 방향으로 SpringArm을 돌리는 각속도이다.
void ACP_Pawn_CombatPlane_KeyInput::StabilizeSpringArm(float _DeltaTime)
{
	if (pSpringArm->GetRelativeRotation() != DefaultSpringArmRotation)
		pSpringArm->SetRelativeRotation(FMath::RInterpTo(pSpringArm->GetRelativeRotation(), DefaultSpringArmRotation, _DeltaTime, 1.f));
}
#pragma endregion StabilizeArea
