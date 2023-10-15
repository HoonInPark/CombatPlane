// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Anim.h"
#include "CP_AI_CombatPlane.h"


/*
* 내가 만든 ACP_Character_Anim 객체가 생성될 때, 
* 그 안에 있는 캐릭터 무브먼트 컴포넌트를 기본적인 것 대신 
* 내가 만든 UCP_CharacterMovementComponent로 설정해라
*/
ACP_Character_Anim::ACP_Character_Anim(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer.SetDefaultSubobjectClass<UCP_CharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 이걸 참조하려면 반드시 GetThisMovComp() 함수를 호출해야 한다. 이 함수는 캡슐화를 위한 기법중 하나이다.
	ThisMovComp = CastChecked<UCP_CharacterMovementComponent>(GetCharacterMovement());

	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	pSpringArm->SetupAttachment(GetCapsuleComponent());
	pSpringArm->TargetArmLength = 1000.f;
	pSpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	pSpringArm->bEnableCameraLag = true;

	pCamera->SetupAttachment(pSpringArm);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Plane(TEXT(
		"/Script/Engine.SkeletalMesh'/Game/_01_BasicSettings/SkeletalMeshes/SK_PLANE/SK_West_UAV_MQ1.SK_West_UAV_MQ1'"));
	if (Plane.Succeeded())
	{
		CPCHECK(Plane.Succeeded());
		GetMesh()->SetSkeletalMesh(Plane.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, 0.f, 0.f));
	}

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;
}

void ACP_Character_Anim::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	UAnimInstance* CurrentAnimInstance = GetMesh()->GetAnimInstance();
	if (!CurrentAnimInstance)
	{
		ThisAnimInstance = NewObject<UCP_AI_CombatPlane>(GetMesh(), UCP_AI_CombatPlane::StaticClass());
		GetMesh()->SetAnimInstanceClass(ThisAnimInstance->GetClass());
		CPLOG(Warning, TEXT(" AnimInstance : %s"), *GetMesh()->GetAnimInstance()->GetName());
	}
	else
		ThisAnimInstance = CurrentAnimInstance;
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
}

void ACP_Character_Anim::ProcessYaw(float _Value)
{
}