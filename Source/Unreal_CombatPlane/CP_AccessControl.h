// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "GameFramework/Actor.h"
#include "CP_AccessControl.generated.h"


UCLASS()
class UNREAL_COMBATPLANE_API ACP_AccessControl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACP_AccessControl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere) // �׳� UPROPERTY()��� ���� �������� �� �� ������ �𸮾� �������÷��Ϳ��� ����ȴ�.
	UStaticMeshComponent* pStaticMeshComponent;

public:
	int32 RockNum;

private:
	float Speed_Mov;
	float Speed_Rot;
	bool DoOnce;
};
