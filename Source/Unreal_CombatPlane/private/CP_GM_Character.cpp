// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_GM_Character.h"

#include "CP_Character_Anim.h"
#include "CP_PC_CombatPlaneController.h"

ACP_GM_Character::ACP_GM_Character()
{
	DefaultPawnClass = ACP_Character_Anim::StaticClass();
	PlayerControllerClass = ACP_PC_CombatPlaneController::StaticClass();
}

void ACP_GM_Character::PostLogin(APlayerController* _NewPlayer)
{
	Super::PostLogin(_NewPlayer);
}

