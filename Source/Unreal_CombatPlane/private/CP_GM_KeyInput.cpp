// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_GM_KeyInput.h"

ACP_GM_KeyInput::ACP_GM_KeyInput()
{
	DefaultPawnClass = ACP_Pawn_CombatPlane_KeyInput::StaticClass();
	PlayerControllerClass = ACP_PC_CombatPlaneController::StaticClass();
}

void ACP_GM_KeyInput::PostLogin(APlayerController* _NewPlayer)
{
	Super::PostLogin(_NewPlayer);
}
