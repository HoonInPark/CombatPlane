// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Unreal_CombatPlane.h"
#include "CP_Pawn_CombatPlane.h"
#include "CP_Pawn_CombatPlane_Tick.h"
#include "CP_PC_CombatPlaneController.h"

#include "GameFramework/GameModeBase.h"
#include "CP_GM_GameModeBase.generated.h"

/**
 * ACP_Pawn_CombatPlane_Tick를 DefaultPawn으로 설정하는 GM 클래스
 */
UCLASS()
class UNREAL_COMBATPLANE_API ACP_GM_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ACP_GM_GameModeBase();

	/* 
	 * public은, 이 클래스가 객체화 된 것에 대해 다른 클래스가 호출했을 때 접근할 수 있다는 의미이다.
	 * 반면 private은, 다른 클래스에서 이 클래스가 객체화된 것에 대해 접근할 수 없다.
	 * private 아래에 선언된 변수, 함수는 다른 클래스가 호출할 수 없다.
	 * 왜 이런걸 만들까?
	 *
	 * 여기 PostLogin은 플레이어가 월드에 입장하는 데에 성공하면 호출되는 이벤트함수이다.
	 * 나중에 멀티플레이 게임을 만들 때, 월드 상에 있는 어떤 객체(몸)에 PlayerController(영혼)를 입힐지,
	 * 즉 빙의(Possess)할지가 관건이 된다.
	 * 이 빙의가 완료되는 것이 곧 로그인이다.
	 * 중단점 찍어서 언제 이 함수가 호출되는지 알아보자~ (그와 함께 언리얼 엔진을 디버깅하는 방법도! Development/Debug Editor로 한다!)
	 */

public:
	virtual void PostLogin(APlayerController* _NewPlayer) override;

};
