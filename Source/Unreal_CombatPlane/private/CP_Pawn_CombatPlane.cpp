// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_Pawn_CombatPlane.h"

// Sets default values
ACP_Pawn_CombatPlane::ACP_Pawn_CombatPlane()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CallNum = 1;
	CPLOG(Warning, TEXT("Call Number : %d"), CallNum++);

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

void ACP_Pawn_CombatPlane::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CPLOG(Warning, TEXT("Call Number : %d"), CallNum++);
}

// Called when the game starts or when spawned
void ACP_Pawn_CombatPlane::BeginPlay()
{
	Super::BeginPlay();

	CPLOG(Warning, TEXT("Call Number : %d"), CallNum++);
}

// Called every frame
void ACP_Pawn_CombatPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACP_Pawn_CombatPlane::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

