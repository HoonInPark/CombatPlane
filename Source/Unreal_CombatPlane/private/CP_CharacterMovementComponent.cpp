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
* UCharacterMovementComponent에서 OnMovementUpdated를 검색해 보면, SimulateMovement의 맨 마지막에 호출된다는 것을 알 수 있다.
* 즉, SimulateMovement를 호출하면 얘가 호출됨. 엔진 소스 보는 법도 알아야 한다. 
* 언리얼 엔진에서 오버라이드된 함수는 부모 클래스의 가상 함수가 호출될 때 영향을 받는다. 
* 부모 클래스에서 가상 함수를 정의하고, 자식 클래스에서 이를 오버라이드하면, 호출 시 자식 클래스의 오버라이드된 버전이 실행된다.
* 우리가 여기서 짤 로직은 일단 캐릭터가 움직인 뒤에 그 움직인 델타 값들을 가져와서 애님 인스턴스에 보내는 것이다.
*/
void UCP_CharacterMovementComponent::OnMovementUpdated(float _DeltaSeconds, const FVector& _OldLocation, const FVector& _OldVelocity)
{
}
#pragma endregion ForMultiplay

void UCP_CharacterMovementComponent::TickComponent(float _DeltaTime, ELevelTick _TickType, FActorComponentTickFunction* _ThisTickFunction)
{
	Super::TickComponent(_DeltaTime, _TickType, _ThisTickFunction);
	
	AddForce(FVector(MaxFlySpeed, 0.f, 0.f));

	const FPawnMovement PawnMovement = { GetDeltaRotation(_DeltaTime), MaxFlySpeed * _DeltaTime }; // 둘 다 가속도이다!
	Execute_PropellerTypeTick(pAnimInstance, PawnMovement);
}

void UCP_CharacterMovementComponent::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void UCP_CharacterMovementComponent::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}
