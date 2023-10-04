// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_CharacterMovementComponent.h"

UCP_CharacterMovementComponent::UCP_CharacterMovementComponent(const FObjectInitializer& _ObjectInitializer)
	: Super(_ObjectInitializer)
{
}

void UCP_CharacterMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UCP_CharacterMovementComponent::TickComponent(float _DeltaTime, ELevelTick _TickType, FActorComponentTickFunction* _ThisTickFunction)
{
	Super::TickComponent(_DeltaTime, _TickType, _ThisTickFunction);

}

void UCP_CharacterMovementComponent::SimulateMovement(float _DeltaTime)
{

}

FRotator UCP_CharacterMovementComponent::GetDeltaRotation(float _DeltaTime) const
{
	return FRotator();
}

float UCP_CharacterMovementComponent::GetMaxSpeed() const
{
	return 0.0f;
}
