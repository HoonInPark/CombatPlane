// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_CharacterMovementComponent.h"
#include "CP_Character_Anim.h"

UCP_CharacterMovementComponent::UCP_CharacterMovementComponent(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	MovementMode = EMovementMode::MOVE_Flying;
	GravityScale = 0.f;
	
	MaxFlySpeed = 1000.f;
	bOrientRotationToMovement = false;
	RotationRate = FRotator(0.f, 720.f, 0.f);
}

void UCP_CharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	pAnimInstance = Cast<ACP_Character_Anim>(GetOwner())->GetThisAnimInst();
}

#pragma region ForMultiplay
void UCP_CharacterMovementComponent::SimulateMovement(float DeltaTime)
{
	Super::SimulateMovement(DeltaTime);

}

/*
* UCharacterMovementComponent���� OnMovementUpdated�� �˻��� ����, SimulateMovement�� �� �������� ȣ��ȴٴ� ���� �� �� �ִ�.
* ��, SimulateMovement�� ȣ���ϸ� �갡 ȣ���. ���� �ҽ� ���� ���� �˾ƾ� �Ѵ�. 
* �𸮾� �������� �������̵�� �Լ��� �θ� Ŭ������ ���� �Լ��� ȣ��� �� ������ �޴´�. 
* �θ� Ŭ�������� ���� �Լ��� �����ϰ�, �ڽ� Ŭ�������� �̸� �������̵��ϸ�, ȣ�� �� �ڽ� Ŭ������ �������̵�� ������ ����ȴ�.
* �츮�� ���⼭ © ������ �ϴ� ĳ���Ͱ� ������ �ڿ� �� ������ ��Ÿ ������ �����ͼ� �ִ� �ν��Ͻ��� ������ ���̴�.
*/
void UCP_CharacterMovementComponent::OnMovementUpdated(float _DeltaSeconds, const FVector& _OldLocation, const FVector& _OldVelocity)
{
}
#pragma endregion ForMultiplay

void UCP_CharacterMovementComponent::TickComponent(float _DeltaTime, ELevelTick _TickType, FActorComponentTickFunction* _ThisTickFunction)
{
	Super::TickComponent(_DeltaTime, _TickType, _ThisTickFunction);
	
	AddForce(FVector(MaxFlySpeed, 0.f, 0.f));

	const FPawnMovement PawnMovement = { GetDeltaRotation(_DeltaTime), MaxFlySpeed * _DeltaTime }; // �� �� ���ӵ��̴�!
	Execute_PropellerTypeTick(pAnimInstance, PawnMovement);
}

void UCP_CharacterMovementComponent::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void UCP_CharacterMovementComponent::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}
