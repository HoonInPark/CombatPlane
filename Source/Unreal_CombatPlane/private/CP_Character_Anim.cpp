// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Character_Anim.h"
#include "CP_AI_CombatPlane.h"

// Sets default values
ACP_Character_Anim::ACP_Character_Anim()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetRelativeRotation(FRotator(-90.f, 0.f, 0.f));
	GetCapsuleComponent()->SetCapsuleHalfHeight(400.f, true);
	GetCapsuleComponent()->SetCapsuleRadius(50.f, true);

	pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	pSpringArm->SetupAttachment(GetCapsuleComponent());
	pSpringArm->TargetArmLength = 1000.f;
	pSpringArm->SetRelativeRotation(FRotator(75.f, 0.f, 0.f));

	pCamera->SetupAttachment(pSpringArm);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> Plane(TEXT("/Script/Engine.SkeletalMesh'/Game/_01_BasicSettings/SkeletalMeshes/SK_PLANE/SK_West_UAV_MQ1.SK_West_UAV_MQ1'"));
	if (Plane.Succeeded())
	{
		CPCHECK(Plane.Succeeded());
		GetMesh()->SetSkeletalMesh(Plane.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(155.f, 0.f, 0.f), FRotator(90.f, 0.f, 0.f));
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
	Super::Tick(DeltaTime);

	AddActorLocalOffset(GetActorForwardVector() * -1000.f * DeltaTime);
}

// Called to bind functionality to input
void ACP_Character_Anim::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UCharacterMovementComponent* CharacterMovement = GetCharacterMovement())
	{
		CharacterMovement->GravityScale = 0;
		CharacterMovement->SetPlaneConstraintNormal(FVector(0.f, 0.f, -1.f)); // Constrain movement to XY plane
		CharacterMovement->SetMovementMode(MOVE_Flying);
	}

}

void ACP_Character_Anim::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void ACP_Character_Anim::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

