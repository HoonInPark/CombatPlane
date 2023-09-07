// Fill out your copyright notice in the Description page of Project Settings.


#include "CP_GM_AnimInst.h"

ACP_GM_AnimInst::ACP_GM_AnimInst()
{
	DefaultPawnClass = ACP_Pawn_AnimInst::StaticClass();
	PlayerControllerClass = ACP_PC_CombatPlaneController::StaticClass();
}

void ACP_GM_AnimInst::PostLogin(APlayerController* _NewPlayer)
{
	Super::PostLogin(_NewPlayer);
}

