#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"

enum class BodyRenderer
{
	UpperBody,
	LowerBody,
	AllBody,
	ZombieArm,
	ZombieLaunchEffect,
	ZombieProjectile,
};

class Marco : public AActor
{
public:
	// constructor destructor
	Marco();
	~Marco();

	// delete Function
	Marco(const Marco& _Other) = delete;
	Marco(Marco&& _Other) noexcept = delete;
	Marco& operator=(const Marco& _Other) = delete;
	Marco& operator=(Marco&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// 상태 보조 함수
	void GravityCheck(float _DeltaTime);
	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	std::string DirCheck(BodyRenderer _BodyRendererType, std::string _Name);
	std::string GunCheck(BodyRenderer _BodyRendererType, std::string _Name);

	std::string AddDirectionName(std::string _CurAnimName);
	std::string AddGunTypeName(std::string _CurAnimName);

	UpperBodyState UpperState = UpperBodyState::Idle;
	LowerBodyState LowerState = LowerBodyState::Idle;
	AllBodyState AllState = AllBodyState::None;
	EActorDir DirState = EActorDir::Right;
	EGunType GunType = EGunType::Pistol;

	void FreeMove(float _DeltaTime);
	void CameraFreeMove(float _DeltaTime);

	void UpperStateUpdate(float _DeltaTime);
	void LowerStateUpdate(float _DeltaTime);
	void AllBodyStateUpdate(float _DeltaTime);

	void UpperStateChange(UpperBodyState _State);
	void LowerStateChange(LowerBodyState _State);
	void AllStateChange(AllBodyState _AllState);

	void UpperIdle(float _DeltaTime);
	void UpperMove(float _DeltaTime);
	void UpperJump(float _DeltaTime);
	void UpperForwardJump(float _DeltaTime);
	void UpperShoot(float _DeltaTime);
	void UpperForwardJumpShoot(float _DeltaTime);
	void UpperThrow(float _DeltaTime);
	void UpperKnifeAttack1(float _DeltaTime);
	void UpperKnifeAttack2(float _DeltaTime);
	void UpperAimNormalToUp(float _DeltaTime);
	void UpperAimUpToNormal(float _DeltaTime);
	void UpperAimUp(float _DeltaTime);
	void UpperAimUpShoot(float _DeltaTime);
	void UpperAimNormalToDown(float _DeltaTime);
	void UpperAimDownToNormal(float _DeltaTime);
	void UpperAimDownShoot(float _DeltaTime);

	void UpperIdleStart();
	void UpperMoveStart();
	void UpperJumpStart();
	void UpperForwardJumpStart();
	void UpperShootStart();
	void UpperForwardJumpShootStart();
	void UpperThrowStart();
	void UpperKnifeAttack1Start();
	void UpperKnifeAttack2Start();
	void UpperAimNormalToUpStart();
	void UpperAimUpToNormalStart();
	void UpperAimUpStart();
	void UpperAimUpShootStart();
	void UpperAimNormalToDownStart();
	void UpperAimDownToNormalStart();
	void UpperAimDownShootStart();
	void UpperStart();


	void LowerIdle(float _DeltaTime);
	void LowerMove(float _DeltaTime);
	void LowerJump(float _DeltaTime);
	void LowerForwardJump(float _DeltaTime);

	void LowerIdleStart();
	void LowerMoveStart();
	void LowerJumpStart();
	void LowerForwardJumpStart();
	void LowerStart();

	void AllSpawn(float _DeltaTime);
	void AllCrouch_Intro(float _DeltaTime);
	void AllCrouch_Outro(float _DeltaTime);
	void AllCrouch_Idle(float _DeltaTime);
	void AllCrouch_Move(float _DeltaTime);
	void AllCrouch_Shoot(float _DeltaTime);
	void AllCrouch_Throw(float _DeltaTime);
	void AllCrouch_KnifeAttack1(float _DeltaTime);
	void AllCrouch_KnifeAttack2(float _DeltaTime);
	void AllCrouch_Ceremony(float _DeltaTime);
	void AllDeath(float _DeltaTime);
	void AllDeathInAir(float _DeltaTime);
	void AllDeathByKnife(float _DeltaTime);
	void ElephantSlug_Idle(float _DeltaTime);
	void ElephantSlug_Move(float _DeltaTime);

	void AllSpawnStart();
	void AllCrouch_IntroStart();
	void AllCrouch_OutroStart();
	void AllCrouch_IdleStart();
	void AllCrouch_MoveStart();
	void AllCrouch_ShootStart();
	void AllCrouch_ThrowStart();
	void AllCrouch_KnifeAttack1Start();
	void AllCrouch_KnifeAttack2Start();
	void AllCrouch_CeremonyStart();
	void AllDeathStart();
	void AllDeathInAirStart();
	void AllDeathByKnifeStart();
	void ElephantSlug_IdleStart();
	void ElephantSlug_Movestart();


	void Zombie_AllTransformToZombie_Intro(float _DeltaTime);
	void Zombie_AllTransformToZombie_Falling(float _DeltaTime);
	void Zombie_AllTransformToZombie_Rising(float _DeltaTime);
	void Zombie_AllIdle(float _DeltaTime);
	void Zombie_AllMove(float _DeltaTime);
	void Zombie_AllTurn(float _DeltaTime);
	void Zombie_AllAimupTurn(float _DeltaTime);
	void Zombie_AllJump(float _DeltaTime);
	void Zombie_AllVomit(float _DeltaTime);
	void Zombie_AllDeath(float _DeltaTime);
	void Zombie_AllDeathInAir(float _DeltaTime);
	
	void Zombie_AllTransformToZombie_IntroStart();
	void Zombie_AllTransformToZombie_FallingStart();
	void Zombie_AllTransformToZombie_RisingStart();
	void Zombie_AllIdleStart();
	void Zombie_AllMoveStart();
	void Zombie_AllTurnStart();
	void Zombie_AllAimupTurnStart();
	void Zombie_AllJumpStart();
	void Zombie_AllVomitStart();
	void Zombie_AllDeathStart();
	void Zombie_AllDeathInAirStart();
	
private:
	std::vector<UImageRenderer*> Renderer;

	std::string CurUpperBodyName = "UpperBody_Idle";
	std::string CurLowerBodyName = "LowerBody_Idle";

	FVector MoveDir = FVector::Zero;
	FVector ShootDir = FVector::Right;
	FVector PrevMoveDir = FVector::Right;


	bool IsZombie = false;
	bool InAir = false;
	bool IsHeavyMachineGun = false;

	int RenderState = 0;
	int PrevRenderState = 0;


	float FreeMoveSpeed = 1000.0f;
	float Gravity = 500.0f;

	float Run_Speed = 300.0f;
	float InAir_Speed = 100.0f;
	float Crouch_Speed = 50.0f;

	float Pistol_Shoot_CoolTime = 0.1f;
	float Pistol_Shoot_AccTime = 0.0f;
	float Pistol_Shoot_EndTime = 0.8f;

	float Throw_CoolTime = 0.1f;
	float Throw_AccTime = 0.0f;
	float Throw_EndTime = 0.8f;
	int RemainBomb = 0;

	float AimNormalToUp_AccTime = 0.0f;
	float AimNormalToUp_Delay = 0.05f;

	float AimNormalToDown_AccTime = 0.0f;
	float AimNormalToDown_Delay = 0.05f;

	float AimDownToNormal_AccTime = 0.0f;
	float AimDownToNormal_Delay = 0.05f;
};

