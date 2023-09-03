// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane.h"
#include "CP_Pawn_CombatPlane_Tick.h"
#include "CP_PC_CombatPlaneController.h"

#include "GameFramework/GameModeBase.h"
#include "CP_GM_GameModeBase.generated.h"

/**
 * ACP_Pawn_CombatPlane_Tick�� DefaultPawn���� �����ϴ� GM Ŭ����
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_GM_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ACP_GM_GameModeBase();

	/* 
	 * public��, �� Ŭ������ ��üȭ �� �Ϳ� ���� �ٸ� Ŭ������ ȣ������ �� ������ �� �ִٴ� �ǹ��̴�.
	 * �ݸ� private��, �ٸ� Ŭ�������� �� Ŭ������ ��üȭ�� �Ϳ� ���� ������ �� ����.
	 * private �Ʒ��� ����� ����, �Լ��� �ٸ� Ŭ������ ȣ���� �� ����.
	 * �� �̷��� �����?
	 *
	 * ���� PostLogin�� �÷��̾ ���忡 �����ϴ� ���� �����ϸ� ȣ��Ǵ� �̺�Ʈ�Լ��̴�.
	 * ���߿� ��Ƽ�÷��� ������ ���� ��, ���� �� �ִ� � ��ü(��)�� PlayerController(��ȥ)�� ������,
	 * �� ����(Possess)������ ������ �ȴ�.
	 * �� ���ǰ� �Ϸ�Ǵ� ���� �� �α����̴�.
	 * �ߴ��� �� ���� �� �Լ��� ȣ��Ǵ��� �˾ƺ���~ (�׿� �Բ� �𸮾� ������ ������ϴ� �����! Development/Debug Editor�� �Ѵ�!)
	 */

public:
	virtual void PostLogin(APlayerController* _NewPlayer) override;

};
