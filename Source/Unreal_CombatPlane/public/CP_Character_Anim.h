// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_AI_CombatPlane.h"
#include "CP_CharacterMovementComponent.h"
#include "CP_Character_Anim.generated.h"

UCLASS()
class UNREAL_COMBATPLANE_API ACP_Character_Anim : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACP_Character_Anim(const FObjectInitializer& _ObjectInitializer = FObjectInitializer::Get());

	/*
	* 
	*/
	UFUNCTION(BlueprintCallable, Category = Movement)
	class UCP_CharacterMovementComponent* GetThisMovComp() const { return ThisMovComp; }
	UFUNCTION(BlueprintCallable, Category = AnimInstance)
	class UAnimInstance* GetThisAnimInst() { return ThisAnimInstance; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PreInitializeComponents() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* pSpringArm;
	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* pCamera;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UCP_CharacterMovementComponent* ThisMovComp; 

private:
	UPROPERTY()
	UAnimInstance* ThisAnimInstance;
	
private:
	void ProcessPitch(float _Value);
	void ProcessYaw(float _Value);

};
