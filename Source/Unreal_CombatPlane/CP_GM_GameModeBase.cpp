// Fill out your copyright notice in the Description page of Project Settings.

#include "CP_GM_GameModeBase.h"

ACP_GM_GameModeBase::ACP_GM_GameModeBase()
{
	/* 
	 * 다음과 같이 기본설정을 해 놓으면 에디터상에서 확인해 볼 수 있다. 다만 에디터에서 수정할 순 없음!
	 * 수정하고 싶다면? BP로 상속!
	 * 부모 클래스에서 설정한 값은 자식 클래스에서 변경할 수 있다.
	 * C++ 클래스를 상속 받은 또 다른 C++ 클래스의 경우, 함수를 상속할 때는
	 * 자식 클래스에서 virtual ~~~~ override를 써준다.
	 * 그러면 이 함수에 대해서는 자식 클래스에서 다르게 작동하도록 만들 수 있다.
	 * 변수는 그냥 값을 바꿔주면 그 바뀐 값이 적용됨.
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
