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
	void InAirCheck();
	// 각 상태마다 언제나 가장 위에 실행되어야 한다.
	std::string DirCheck(BodyRenderer _BodyRendererType, std::string _Name);
	std::string GunCheck(BodyRenderer _BodyRendererType, std::string _Name);

	std::string AddDirectionName(std::string _CurAnimName);
	std::string AddGunTypeName(std::string _CurAnimName);
	void HeavyMachineGunCheckName(std::string& CurAnimName);
	void GunTypeShootCheck();
	void TriggerDirCheck(BodyRenderer _BodyRenderer, std::string _Name);

	UpperBodyState UpperState = UpperBodyState::Idle;
	LowerBodyState LowerState = LowerBodyState::Idle;
	AllBodyState AllState = AllBodyState::None;
	EActorDir DirState = EActorDir::Right;
	EGunType GunType = EGunType::Pistol;
	EGunList Gun = EGunList::Pistol;

	void FreeMove(float _DeltaTime);
	void CameraFreeMove(float _DeltaTime);

	void UpperStateUpdate(float _DeltaTime);
	void LowerStateUpdate(float _DeltaTime);
	void AllBodyStateUpdate(float _DeltaTime);

	void UpperStateChange(UpperBodyState _State);
	void LowerStateChange(LowerBodyState _State);
	void AllStateChange(AllBodyState _AllState);

	void UpperNone(float _DeltaTime);
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
	void UpperAimNormalToUpShoot(float _DeltaTime);
	void UpperAimUpToNormalShoot(float _DeltaTime);
	void UpperAimNormalToDownShoot(float _DeltaTime);
	void UpperAimDownToNormalShoot(float _DeltaTime);

	void UpperNoneStart();
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
	void UpperAimNormalToUpShootStart();
	void UpperAimUpToNormalShootStart();
	void UpperAimNormalToDownShootStart();
	void UpperAimDownToNormalShootStart();

	void UpperStart();

	void LowerNone(float _DeltaTime);
	void LowerIdle(float _DeltaTime);
	void LowerMove(float _DeltaTime);
	void LowerJump(float _DeltaTime);
	void LowerForwardJump(float _DeltaTime);

	void LowerNoneStart();
	void LowerIdleStart();
	void LowerMoveStart();
	void LowerJumpStart();
	void LowerForwardJumpStart();
	void LowerStart();

	void AllSpawn(float _DeltaTime);
	void AllNone(float _DeltaTime);
	void AllCrouch_Intro(float _DeltaTime);
	void AllCrouch_Outro(float _DeltaTime);
	void AllCrouch_Idle(float _DeltaTime);
	void AllCrouch_Move(float _DeltaTime);
	void AllCrouch_Shoot(float _DeltaTime);
	void AllCrouch_HeavyMachineGun_Shoot(float _DeltaTime);
	void AllCrouch_Throw(float _DeltaTime);
	void AllCrouch_KnifeAttack1(float _DeltaTime);
	void AllCrouch_KnifeAttack2(float _DeltaTime);
	void AllCeremony(float _DeltaTime);
	void AllDeath(float _DeltaTime);
	void AllDeathInAir(float _DeltaTime);
	void AllDeathByKnife(float _DeltaTime);
	void AllElephantSlug_Idle(float _DeltaTime);
	void AllElephantSlug_Move(float _DeltaTime);

	void AllSpawnStart();
	void AllNoneStart();
	void AllCrouch_IntroStart();
	void AllCrouch_OutroStart();
	void AllCrouch_IdleStart();
	void AllCrouch_MoveStart();
	void AllCrouch_ShootStart();
	void AllCrouch_HeavyMachineGun_ShootStart();
	void AllCrouch_ThrowStart();
	void AllCrouch_KnifeAttack1Start();
	void AllCrouch_KnifeAttack2Start();
	void AllCeremonyStart();
	void AllDeathStart();
	void AllDeathInAirStart();
	void AllDeathByKnifeStart();
	void AllElephantSlug_IdleStart();
	void AllElephantSlug_MoveStart();
	void AllStart();


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
	void ZombieStart();
	
private:
	std::vector<UImageRenderer*> Renderer;

	std::string CurUpperBodyName = "UpperBody_Idle";
	std::string CurLowerBodyName = "LowerBody_Idle";
	std::string CurAllBodyName = "Crouch_Idle";

	FVector MoveDir = FVector::Zero;
	FVector ShootDir = FVector::Right;
	FVector PrevMoveDir = FVector::Right;


	bool IsZombie = false;
	bool InAir = false;
	bool IsHeavyMachineGun = false;

	int RenderState = 0;
	int PrevRenderState = 0;

	float FreeMoveSpeed = 1000.0f;
	float Gravity = 800.0f;
	float FallSpeed = 0.0f;


	float AimNormalToUp_AccTime = 0.0f;
	float AimNormalToUp_Delay = 0.16f;

	float AimNormalToDown_AccTime = 0.0f;
	float AimNormalToDown_Delay = 0.16f;

	float AimDownToNormal_AccTime = 0.0f;
	float AimDownToNormal_Delay = 0.16f;

	float AimNormalToUpShoot_AccTime = 0.0f;
	float AimNormalToUpShoot_Delay = 0.2f;

	float AimNormalToDownShoot_AccTime = 0.0f;
	float AimNormalToDownShoot_Delay = 0.2f;

	float AimDownToNormalShoot_AccTime = 0.0f;
	float AimDownToNormalShoot_Delay = 0.2f;

	float CrouchIntro_AccTime = 0.0f;
	float CrouchIntro_Delay = 0.05f;

	float* AccTime = nullptr;
	float* CoolTime = nullptr;
	float* EndTime = nullptr;

	float Run_Speed = 300.0f;
	float InAir_Speed = 100.0f;
	float Crouch_Speed = 50.0f;

	float Pistol_Shoot_CoolTime = 0.1f;
	float Pistol_Shoot_AccTime = 0.0f;
	float Pistol_Shoot_EndTime = 0.8f;

	float HeavyMachineGun_Shoot_AccTime = 0.0f;
	float HeavyMachineGun_Shoot_CoolTime = 0.14f;
	float HeavyMachineGun_Shoot_EndTime = 0.28f;

	float FlameShot_Shoot_AccTime = 0.0f;
	float FlameShot_Shoot_CoolTime = 0.35f;
	float FlameShot_Shoot_EndTime = 0.4f;

	float ShotGun_Shoot_AccTime = 0.0f;
	float ShotGun_Shoot_CoolTime = 0.3f;
	float ShotGun_Shoot_EndTime = 0.35f;

	float RocketLauncher_Shoot_AccTime = 0.0f;
	float RocketLauncher_Shoot_CoolTime = 0.3f;
	float RocketLauncher_Shoot_EndTime = 0.35f;

	float IronLizard_Shoot_AccTime = 0.0f;
	float IronLizard_Shoot_CoolTime = 0.3f;
	float IronLizard_Shoot_EndTime = 0.35f;

	float Throw_CoolTime = 0.1f;
	float Throw_AccTime = 0.0f;
	float Throw_EndTime = 0.8f;
	int RemainBomb = 0;

	FVector MarcoUpperBodyPosition = { 0.0f,-23.0f };
	FVector MarcoSize = { 527.27273f, 527.27273f };
	FVector Moving_UpperBodyOffset = { 0.0f,-6.0f };
	FVector Juming_UpperBodyOffset = { -4.0f,-17.0f };
	FVector ForwardJumping_UpperBodyOffset = { -9.0f ,-14.0f };
	FVector Juming_UpperBodyOffset_Right = { -4.0f,-17.0f };
	FVector Juming_UpperBodyOffset_Left = { 4.0f,-17.0f };
	FVector ForwardJumping_UpperBodyOffset_Right = { -9.0f ,-14.0f };
	FVector ForwardJumping_UpperBodyOffset_Left = { 9.0f ,-14.0f };

	void Moving_UpperBodySyncro();
	void Jumping_UpperBodySyncro();
	void ForwardJumping_UpperBodySyncro();
	void Reset_UpperBodySyncro();

};

