// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Anim.h"
#include "CP_AI_CombatPlane.h"

// Sets default values
ACP_Character_Anim::ACP_Character_Anim(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer.SetDefaultSubobjectClass<UCP_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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
}

// Called to bind functionality to input
void ACP_Character_Anim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACP_Character_Anim::ProcessPitch);
	//PlayerInputComponent->BindAxis(TEXT("TurnAround"), this, &ACP_Character_Anim::ProcessYaw);
}

void ACP_Character_Anim::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Character_Anim::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}
