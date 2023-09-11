// Fill out your copyright notice in the Description page of Project Settings.

#include "CP_GM_GameModeBase.h"

ACP_GM_GameModeBase::ACP_GM_GameModeBase()
{
	/* 
	 * ������ ���� �⺻������ �� ������ �����ͻ󿡼� Ȯ���� �� �� �ִ�. �ٸ� �����Ϳ��� ������ �� ����!
	 * �����ϰ� �ʹٸ�? BP�� ���!
	 * �θ� Ŭ�������� ������ ���� �ڽ� Ŭ�������� ������ �� �ִ�.
	 * C++ Ŭ������ ��� ���� �� �ٸ� C++ Ŭ������ ���, �Լ��� ����� ����
	 * �ڽ� Ŭ�������� virtual ~~~~ override�� ���ش�.
	 * �׷��� �� �Լ��� ���ؼ��� �ڽ� Ŭ�������� �ٸ��� �۵��ϵ��� ���� �� �ִ�.
	 * ������ �׳� ���� �ٲ��ָ� �� �ٲ� ���� �����.
	 */
	//DefaultPawnClass = ACP_Pawn_CombatPlane::StaticClass();

	/*
	DefaultPawnClass = ACP_Pawn_CombatPlane_KeyInput::StaticClass();
	*/
	DefaultPawnClass = ACP_Pawn_CombatPlane_Tick::StaticClass();
	PlayerControllerClass = ACP_PC_CombatPlaneController::StaticClass();
}

void ACP_GM_GameModeBase::PostLogin(APlayerController* _NewPlayer)
{
	Super::PostLogin(_NewPlayer);

}
