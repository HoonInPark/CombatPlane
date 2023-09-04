// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "UObject/Interface.h"
#include "CP_Pawn_To_AnimInstance.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCP_Pawn_To_AnimInstance : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UNREAL_COMBATPLANE_API ICP_Pawn_To_AnimInstance
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void PropellerTypeTick();
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interface")
	void JetEngineTypeTick();

};
