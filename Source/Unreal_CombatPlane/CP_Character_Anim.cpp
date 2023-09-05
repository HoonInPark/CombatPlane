// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Anim.h"

// Sets default values
ACP_Character_Anim::ACP_Character_Anim()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
}

// Called every frame
void ACP_Character_Anim::Tick(float DeltaTime)
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
	DeltaRotation.Pitch = CurrentSpeed_Pitch * DeltaTime; // 위/아래!
	DeltaRotation.Yaw = CurrentSpeed_Yaw * DeltaTime; // 양 옆!

	// Roll 축의 수평을 유지해 주는 코드
#pragma region MaintainPlane
	const float CurrentAngle_Roll = GetActorRotation().Roll;
	const float TargetSpeed_Roll = -CurrentAngle_Roll * 1.f;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, DeltaTime, 2.f);
	DeltaRotation.Roll = CurrentSpeed_Roll * DeltaTime;
#pragma endregion MaintainPlane

	AddActorLocalRotation(DeltaRotation);
#pragma endregion InterpAxisMapping

}

// Called to bind functionality to input
void ACP_Character_Anim::SetupPlayerInputComponent(UInputComponent* _InputComponent)
{
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
	CurrentSpeed_Yaw = FMath::FInterpTo(CurrentSpeed_Yaw, TargetSpeed_Yaw, GetWorld()->GetDeltaSeconds(), 2.f);

	const float TargetSpeed_Roll = _Value * AxisSpeed;
	CurrentSpeed_Roll = FMath::FInterpTo(CurrentSpeed_Roll, TargetSpeed_Roll, GetWorld()->GetDeltaSeconds(), 1.f);

}

void ACP_Character_Anim::PropellerTypeTick_Implementation()
{
}

void ACP_Character_Anim::JetEngineTypeTick_Implementation()
{
}
