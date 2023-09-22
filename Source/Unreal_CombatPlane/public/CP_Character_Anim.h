// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_To_AnimInst.h"
#include "CP_Character_Anim.generated.h"

UCLASS()
class UNREAL_COMBATPLANE_API ACP_Character_Anim : public ACharacter, public ICP_Pawn_To_AnimInst
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACP_Character_Anim();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	enum class EControlMode
	{
		FLY,
		FIRE
	};
	void SetControlMode(EControlMode _NewControlMode);
	EControlMode CurrentControlMode;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

private:
	virtual void PropellerTypeTick_Implementation(FPawnMovement _PawnMovement) override;
	virtual void JetEngineTypeTick_Implementation(FPawnMovement _PawnMovement) override;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* pSpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* pCamera;

private:
	UPROPERTY()
	UAnimInstance* pAnimInstance;

	void ApplyForwardThrust(float _Value);
	void ApplyRightThrust(float _Value);
	void ApplyUpThrust(float _Value);
	
	void ProcessPitch(float _Value);
	void ProcessYaw(float _Value);
	void ProcessRoll(float _Value);

	
};
