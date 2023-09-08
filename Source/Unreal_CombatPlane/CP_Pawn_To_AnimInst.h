// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "UObject/Interface.h"
#include "CP_Pawn_To_AnimInst.generated.h"

USTRUCT(BlueprintType)
struct FPawnMovement
{
	GENERATED_BODY()

	UPROPERTY()
	FRotator Speed_Rotation;
	UPROPERTY()
	float Speed_Move;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCP_Pawn_To_AnimInst : public UInterface
{
	GENERATED_BODY()
};

/**
 * �츮�� ���� Pawn���� �ӵ��� ���� ���� �����ͼ� AnimInstance�� �������ְ��� �Ѵ�.
 * UInterface�� ���� �̰��� ����� �������� Ŭ���� �� �ϳ��� _Implementation�� ���� �������̽��� �Լ��� ȣ���ϸ�
 * �ٸ� Ŭ�������� ������ _Implementation�� ���� �������̽��� �Լ��� ���ÿ� ȣ��Ǵ� ������ �Ѵ�.
 * ��, ���� ������(����� �θ�, ������Ʈ�� ����ƴ��� ���� ���)�� ��� Cast�� GetPawnOwner ���� Ű���带 �� �� ���� �� ����Ѵ�.
 * �츮�� ���⼭ �������̽��� ���� ������, �ִϸ��̼��� �ִԺ����ιۿ� ���ϱ� ������ �ִϸ��̼� ������ �Ϻΰ� �������Ʈ���� �Ʊ� �����̴�.
 * UE5���� ������ C++ �ڵ忡�� �����ϴ� ���� �ٶ������� �ʴ�. ���� ������ �������� ������ AnimInstance�� �������̽� �Լ��� ������ ����, 
 * �Ȱ��� �ñ״�ó�� �������̽� �Լ��� Pawn���� ������ �ִ� ���� �ڿ�������. �� �� �Լ��� ���� ���� ���� �ְ���� �� �ִ�.
 */
//struct FPawnMovement;

class UNREAL_COMBATPLANE_API ICP_Pawn_To_AnimInst
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void PropellerTypeTick(FPawnMovement _PawnMovement);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void JetEngineTypeTick(FPawnMovement _PawnMovement);

};
