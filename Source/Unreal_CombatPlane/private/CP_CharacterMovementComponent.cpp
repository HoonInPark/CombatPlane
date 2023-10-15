// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_CharacterMovementComponent.h"
#include "CP_Character_Anim.h"

UCP_CharacterMovementComponent::UCP_CharacterMovementComponent(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	MovementMode = EMovementMode::MOVE_Flying;
	GravityScale = 0.f;
	
	Mass = 1.f;
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
void UCP_CharacterMovementComponent::SimulatedTick(float DeltaSeconds)
{
	Super::SimulatedTick(DeltaSeconds);

}

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
	
	// Mass의 디폴트 값이 100으로 설정돼 있었고, 이 변수가 AddForce의 속도에 관여하고 있었다. 그래서 1으로 값을 낮춰줌.
	AddForce(FVector(MaxFlySpeed, 0.f, 0.f));
	
	CPLOG(Warning, TEXT(" GetDeltaRotation(_DeltaTime) : %s"), *GetDeltaRotation(_DeltaTime).ToString());
	/*
	* 위 로그에 대해 아래와 같은 결과값이 나옴. 왜 Pitch와 Roll은 계속 0.f가 나오는 거지?
	* Yaw의 경우 심지어 마우스 인풋이 안들어가도 값이 들어간다.
	* Unreal_CombatPlane: Warning: UCP_CharacterMovementComponent::TickComponent(60) GetDeltaRotation(_DeltaTime) : P=0.000000 Y=13.935385 R=0.000000
	* Unreal_CombatPlane: Warning: UCP_CharacterMovementComponent::TickComponent(60) GetDeltaRotation(_DeltaTime) : P=0.000000 Y=18.544750 R=0.000000
	* Unreal_CombatPlane: Warning: UCP_CharacterMovementComponent::TickComponent(60) GetDeltaRotation(_DeltaTime) : P=0.000000 Y=12.000024 R=0.000000
	* Unreal_CombatPlane: Warning: UCP_CharacterMovementComponent::TickComponent(60) GetDeltaRotation(_DeltaTime) : P=0.000000 Y=12.000095 R=0.000000
	* Unreal_CombatPlane: Warning: UCP_CharacterMovementComponent::TickComponent(60) GetDeltaRotation(_DeltaTime) : P=0.000000 Y=14.548179 R=0.000000
	* Unreal_CombatPlane: Warning: UCP_CharacterMovementComponent::TickComponent(60) GetDeltaRotation(_DeltaTime) : P=0.000000 Y=14.910695 R=0.000000
	*/
	const FPawnMovement PawnMovement = { GetDeltaRotation(_DeltaTime), MaxFlySpeed * _DeltaTime }; // 둘 다 가속도이다!
	Execute_PropellerTypeTick(pAnimInstance, PawnMovement);
}

void UCP_CharacterMovementComponent::PropellerTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}

void UCP_CharacterMovementComponent::JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement)
{
}
