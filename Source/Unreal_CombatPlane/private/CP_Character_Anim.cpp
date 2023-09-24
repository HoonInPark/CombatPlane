// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Anim.h"
#include "CP_AI_CombatPlane.h"

// Sets default values
ACP_Character_Anim::ACP_Character_Anim()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	pSpringArm->SetupAttachment(GetCapsuleComponent());
	pSpringArm->TargetArmLength = 1000.f;
	pSpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	pCamera->SetupAttachment(pSpringArm);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Plane(TEXT(
		"/Script/Engine.SkeletalMesh'/Game/_01_BasicSettings/SkeletalMeshes/SK_PLANE/SK_West_UAV_MQ1.SK_West_UAV_MQ1'"));
	if (Plane.Succeeded())
	{
		CPCHECK(Plane.Succeeded());
		GetMesh()->SetSkeletalMesh(Plane.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, 0.f, 0.f));
	}
	
	// 기본적인 Pawn의 움직임을 정해준다.
	GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	GetCharacterMovement()->GravityScale = 0.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
}

void ACP_Character_Anim::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// GetBaseRotationOffset().Rotator() = FRotator(90.f, 0.f, 0.f);

	UAnimInstance* CurrentAnimInstance = GetMesh()->GetAnimInstance();
	if (!CurrentAnimInstance)
	{
		pAnimInstance = NewObject<UCP_AI_CombatPlane>(GetMesh(),
		                                              UCP_AI_CombatPlane::StaticClass());
		GetMesh()->SetAnimInstanceClass(pAnimInstance->GetClass());
		CPLOG(Warning, TEXT(" AnimInstance : %s"), *GetMesh()->GetAnimInstance()->GetName());
	}
	else
		pAnimInstance = CurrentAnimInstance;
}

// Called when the game starts or when spawned
void ACP_Character_Anim::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACP_Character_Anim::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	pSpringArm->bEnableCameraLag = true;
	pSpringArm->CameraLagSpeed = LocalMove_Delta / 1000.f;
	
	const FPawnMovement PawnMovement = {10.f * FRotator(CurrentInput_Pitch, CurrentInput_Yaw, 0.f)
		, AddLocalMove(DeltaTime)
	};
	Execute_PropellerTypeTick(
		pAnimInstance, PawnMovement
	);
}

// Called to bind functionality to input
void ACP_Character_Anim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Character_Anim::ProcessPitch);
	PlayerInputComponent->BindAxis(TEXT("TurnAround"), this, &ACP_Character_Anim::ProcessYaw);
}

void ACP_Character_Anim::ProcessPitch(float _Value)
{
	const float TargetInput_Pitch = _Value;
	CurrentInput_Pitch = FMath::FInterpTo(CurrentInput_Pitch, TargetInput_Pitch, GetWorld()->GetDeltaSeconds(), 0.5f);
	AddControllerPitchInput(-CurrentInput_Pitch); // 이유는 모르겠으나 Pitch 입력을 반대로 먹여줘야 했다.
}

void ACP_Character_Anim::ProcessYaw(float _Value)
{
	const float TargetInput_Yaw = _Value;
	CurrentInput_Yaw = FMath::FInterpTo(CurrentInput_Yaw, TargetInput_Yaw, GetWorld()->GetDeltaSeconds(), 0.5f);
	AddControllerYawInput(CurrentInput_Yaw);
}

float ACP_Character_Anim::AddLocalMove(float _DeltaTime)
{
	LocalMove_Delta = FMath::FInterpTo(LocalMove_Delta, 10000.f, _DeltaTime, 0.25f);
	const FVector LocalMove_AnimInst = FVector(_DeltaTime * LocalMove_Delta, 0.f, 0.f);
	AddActorLocalOffset(LocalMove_AnimInst);

	return LocalMove_AnimInst.X;
}

void ACP_Character_Anim::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Character_Anim::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}
