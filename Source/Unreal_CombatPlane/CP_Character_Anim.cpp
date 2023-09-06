// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Anim.h"

// Sets default values
ACP_Character_Anim::ACP_Character_Anim()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bDebuggingState = false;

	pBodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PLANEBODY"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = pBodyMeshComp;
	pCamera->SetupAttachment(pBodyMeshComp);
	pCamera->SetRelativeLocation(FVector(-500.f, 0.f, 250.f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Plane(TEXT("/Script/Engine.SkeletalMesh'/Game/_01_BasicSettings/SkeletalMeshes/SK_PLANE/SK_West_UAV_MQ1.SK_West_UAV_MQ1'"));
	if (Plane.Succeeded())
	{
		CPCHECK(Plane.Succeeded());
		pBodyMeshComp->SetSkeletalMesh(Plane.Object);
	}
}

// Called when the game starts or when spawned
void ACP_Character_Anim::BeginPlay()
{
	Super::BeginPlay();
	
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();

	// Set a timer to call our function after 5 seconds
	TimerManager.SetTimer(TimerHandle, this, &ACP_Character_Anim::SetDebuggingMode, 5.0f, false);

}

// Called every frame
void ACP_Character_Anim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector LocalMove = FVector(DeltaTime * 5000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * DeltaTime;
	DeltaRotation.Yaw = CurrentSpeed_Yaw * DeltaTime;

	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, DeltaTime, 2.f);
	DeltaRotation.Roll = CurrentSpeed_Roll * DeltaTime;

	AddActorLocalRotation(DeltaRotation);

	/*
	if (!bDebuggingState)
		NonDebuggingTick(DeltaTime);
	else
		DebuggingTick(DeltaTime);
	*/
}

// Called to bind functionality to input
void ACP_Character_Anim::SetupPlayerInputComponent(UInputComponent* _InputComponent)
{
	Super::SetupPlayerInputComponent(_InputComponent);
	
	_InputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Character_Anim::ProcessPitch); // delegate!
	_InputComponent->BindAxis(TEXT("TurnAround"), this, &ACP_Character_Anim::ProcessYaw);
}

void ACP_Character_Anim::ProcessPitch(float _Value)
{
	const float TargetSpeed_Pitch = _Value * AxisSpeed;
	CurrentSpeed_Pitch = FMath::FInterpTo(CurrentSpeed_Pitch, TargetSpeed_Pitch, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ACP_Character_Anim::ProcessYaw(float _Value)
{
	const float TargetSpeed_Yaw = _Value * AxisSpeed;
	CurrentSpeed_Yaw = FMath::FInterpTo(CurrentSpeed_Yaw, TargetSpeed_Yaw, this->GetWorld()->GetDeltaSeconds(), 2.f);
	//CPLOG(Warning, TEXT(" TargetSpeed_Yaw : %f"), TargetSpeed_Yaw);

	const float TargetSpeed_Roll = _Value * AxisSpeed;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, this->GetWorld()->GetDeltaSeconds(), 1.f);

}

#pragma region DebuggingArea
void ACP_Character_Anim::SetDebuggingMode()
{
	bDebuggingState = true;
	CPLOG(Warning, TEXT(" bDebuggingState : %b"), bDebuggingState);
}

void ACP_Character_Anim::NonDebuggingTick(float _DeltaTime)
{
	const FVector LocalMove = FVector(_DeltaTime * 5000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * _DeltaTime;
	DeltaRotation.Yaw = CurrentSpeed_Yaw * _DeltaTime;

	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, _DeltaTime, 2.f);
	DeltaRotation.Roll = CurrentSpeed_Roll * _DeltaTime;

	AddActorLocalRotation(DeltaRotation);
}

void ACP_Character_Anim::DebuggingTick(float _DeltaTime)
{
	const FVector LocalMove = FVector(_DeltaTime * 5000.f, 0.f, 0.f);
	AddActorLocalOffset(LocalMove);

	FRotator DeltaRotation;
	DeltaRotation.Pitch = CurrentSpeed_Pitch * _DeltaTime; 
	DeltaRotation.Yaw = CurrentSpeed_Yaw * _DeltaTime;

	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, _DeltaTime, 2.f);
	DeltaRotation.Roll = CurrentSpeed_Roll * _DeltaTime;

	AddActorLocalRotation(DeltaRotation);
}
#pragma endregion DebuggingArea

void ACP_Character_Anim::PropellerTypeTick_Implementation()
{
}

void ACP_Character_Anim::JetEngineTypeTick_Implementation()
{
}
