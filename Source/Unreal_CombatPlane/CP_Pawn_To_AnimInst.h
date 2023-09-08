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
 * 우리는 지금 Pawn에서 속도와 각도 값을 가져와서 AnimInstance에 전달해주고자 한다.
 * UInterface는 보통 이것을 상속한 여러개의 클래스 중 하나가 _Implementation이 붙은 인터페이스의 함수를 호출하면
 * 다른 클래스에서 구현된 _Implementation이 붙은 인터페이스의 함수도 동시에 호출되는 역할을 한다.
 * 즉, 서로 공통점(공통된 부모, 컴포넌트로 연결됐는지 여부 등등)이 없어서 Cast나 GetPawnOwner 같은 키워드를 쓸 수 없을 때 사용한다.
 * 우리가 여기서 인터페이스를 쓰는 이유는, 애니메이션은 애님블프로밖에 못하기 때문에 애니메이션 구현의 일부가 블루프린트에서 됐기 때문이다.
 * UE5에서 블프를 C++ 코드에서 참조하는 것은 바람직하지 않다. 따라서 블프의 조상으로 설정한 AnimInstance에 인터페이스 함수를 구현한 다음, 
 * 똑같은 시그니처의 인터페이스 함수를 Pawn에서 구현해 주는 것이 자연스럽다. 이 두 함수를 통해 서로 값을 주고받을 수 있다.
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
