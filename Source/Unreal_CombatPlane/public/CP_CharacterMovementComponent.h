// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CP_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREAL_COMBATPLANE_API UCP_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UCP_CharacterMovementComponent(const FObjectInitializer& _ObjectInitializer);

	virtual void SimulateMovement(float _DeltaTime) override;
	virtual FRotator GetDeltaRotation(float _DeltaTime) const override;
	virtual float GetMaxSpeed() const override;

protected:
	virtual void InitializeComponent() override;
	virtual void TickComponent(float _DeltaTime, enum ELevelTick _TickType, FActorComponentTickFunction* _ThisTickFunction	) override;
};
