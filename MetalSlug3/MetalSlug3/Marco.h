#pragma once
#include <EngineCore\Actor.h>
#include "ContentsHelper.h"
#include "ZombieVomitProjectile.h"

enum class BodyRenderer
{
	UpperBody,
	LowerBody,
	AllBody,
	ZombieArm,
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

	bool IsZombie = false;
	bool IsDeath = false;

	int ArmsCount = 200;
	int BombsCount = 10;
	int RemainBomb = 2;

	EGunType GunType = EGunType::Pistol;
	EGunList Gun = EGunList::Pistol;
	EActorDir DirState = EActorDir::Right;
	void ZombieToHuman();

	void UpperStateChange(UpperBodyState _State);
	void LowerStateChange(LowerBodyState _State);
	void AllStateChange(AllBodyState _AllState);
	void ZombieArmStateChange(ZombieArmState _State);

	inline void ManipulateOn()
	{
		Manipulate = true;
	}

	inline void ManipulateOff()
	{
		Manipulate = false;
	}

	void AutoMoveOn()
	{
		IsAutoMove = true;
	}

	void AutoMoveOff()
	{
		IsAutoMove = false;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	// 상태 보조 함수
	void GravityCheck(float _DeltaTime);
	void InAirCheck(float _DeltaTime);
	void DeathCheck();
	void ManipulateUpdate(float _DeltaTime);

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
	ZombieArmState ZArmState = ZombieArmState::None;

	void UpperStateUpdate(float _DeltaTime);
	void LowerStateUpdate(float _DeltaTime);
	void AllBodyStateUpdate(float _DeltaTime);
	void ZombieArmStateUpdate(float _DeltaTime);


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

	void ZombieArm_None(float _DeltaTime);
	void ZombieArm_Idle(float _DeltaTime);
	void ZombieArm_Idle_AimUp(float _DeltaTime);
	void ZombieArm_Move(float _DeltaTime);
	void ZombieArm_Move_AimUp(float _DeltaTime);
	void ZombieArm_Jump(float _DeltaTime);
	void ZombieArm_Jump_AimUp(float _DeltaTime);
	void ZombieArm_Shoot(float _DeltaTime);
	void ZombieArm_Shoot_AimUp(float _DeltaTime);
	void ZombieArm_AimNormalToUp(float _DeltaTime);
	void ZombieArm_AimUpToNormal(float _DeltaTime);

	void ZombieArm_NoneStart();
	void ZombieArm_IdleStart();
	void ZombieArm_Idle_AimUpStart();
	void ZombieArm_MoveStart();
	void ZombieArm_Move_AimUpStart();
	void ZombieArm_JumpStart();
	void ZombieArm_Jump_AimUpStart();
	void ZombieArm_ShootStart();
	void ZombieArm_Shoot_AimUpStart();
	void ZombieArm_AimNormalToUpStart();
	void ZombieArm_AimUpToNormalStart();
	void ZombieArmStart();
	
private:
	std::vector<UImageRenderer*> Renderer;
	UCollision* Collision = nullptr;
	UCollision* KnifeReach = nullptr;
	UCollision* GroundCheckCol = nullptr;
	UCollision* RightCheckCol = nullptr;
	UCollision* LeftCheckCol = nullptr;

	std::string CurUpperBodyName = "UpperBody_Idle";
	std::string CurLowerBodyName = "LowerBody_Idle";
	std::string CurAllBodyName = "Crouch_Idle";
	std::string CurZArmName = "ZombieArm_Idle";

	FVector ShootDir = FVector::Right;

	void Jumping_UpperBodySyncro();
	void ForwardJumping_UpperBodySyncro();
	void Reset_UpperBodySyncro();
	void ZombieArm_Syncro();
	void CalGravityVector(float _DeltaTime);
	void GroundUp();
	void BulletSpawn(FVector _SpawnLocation, FVector _BulletDir);


	bool InAir = false;
	bool IsHeavyMachineGun = false;
	bool IsCrouching = false;
	bool CrouchShooting = false;
	bool Manipulate = true;
	bool NoHit = true;

	float FreeMoveSpeed = 1000.0f;

	float* AccTime = nullptr;
	float* CoolTime = nullptr;

	float Move_Speed = 300.0f;
	float Run_Speed = 300.0f;
	float Jump_Speed = 150.0f;
	float ForwardJump_Speed = 200.0f;
	float Crouch_Speed = 50.0f;
	float Zombie_Speed = 75.0f;
	
	float Pistol_Shoot_CoolTime = 0.1f;
	float Pistol_Shoot_AccTime = 0.0f;

	float HeavyMachineGun_Shoot_AccTime = 0.0f;
	float HeavyMachineGun_Shoot_CoolTime = 0.14f;

	float FlameShot_Shoot_AccTime = 0.0f;
	float FlameShot_Shoot_CoolTime = 0.35f;

	float ShotGun_Shoot_AccTime = 0.0f;
	float ShotGun_Shoot_CoolTime = 0.3f;

	float RocketLauncher_Shoot_AccTime = 0.0f;
	float RocketLauncher_Shoot_CoolTime = 0.3f;

	float IronLizard_Shoot_AccTime = 0.0f;
	float IronLizard_Shoot_CoolTime = 0.3f;

	float Throw_CoolTime = 0.1f;
	float Throw_AccTime = 0.0f;
	

	int HeavyMachineGun_PrevFrame = -1;
	int Vomit_PrevFrame = -1;
	int Jump_PrevFrame = -1;

	bool IsVomitProjectileCol = false;
	int iterator = 0;
	std::vector<AZombieVomitProjectile*> VomitProjectileVec;

	FVector MarcoUpperBodyOffset = { 0.0f, 0.0f };
	FVector MarcoDefaultUpperBodyOffset = { 0.0f,-23.0f };
	FVector MarcoSize = { 527.27273f, 527.27273f };
	FVector Juming_UpperBodyOffset = { -4.0f,-17.0f };
	FVector ForwardJumping_UpperBodyOffset = { -9.0f ,-14.0f };
	FVector Juming_UpperBodyOffset_Right = { -4.0f,-17.0f };
	FVector Juming_UpperBodyOffset_Left = { 4.0f,-17.0f };
	FVector ForwardJumping_UpperBodyOffset_Right = { -9.0f ,-14.0f };
	FVector ForwardJumping_UpperBodyOffset_Left = { 9.0f ,-14.0f };
	FVector ZombieArm_Offset_Right = { 10,-60 };
	FVector ZombieArm_Offset_Left = { -10,-60 };

	FVector Standing_BulletSpawnOffset = { 0,-47 };
	FVector Standing_RifleBulletSpawnOffset = { 0,-37 };
	FVector Crouching_BulletSpawnOffset = { 0, -43 };

	FVector AimUp_BulletSpawnOffset_Right = { 2,-75 };
	FVector AimUp_BulletSpawnOffset_Left = { 0,-75 };
	FVector AimDown_BulletSpawnOffset_Right = { 7,25 };
	FVector AimDown_BulletSpawnOffset_Left = { -7,25 };

	FVector AimUp_RifleBulletSpawnOffset_Right = { -5,-130 };
	FVector AimUp_RifleBulletSpawnOffset_Left = { 5,-130 };
	FVector AimDown_RifleBulletSpawnOffset_Right = { -10,90 };
	FVector AimDown_RifleBulletSpawnOffset_Left = { 10,90 };

	FVector BulletSpawnOffset_Right = { 75,0 };
	FVector BulletSpawnOffset_Left = { -75,0 };

	FVector GravityVector = FVector::Zero;
	FVector Gravity = FVector::Down * 1300.0f;

	FVector JumpPower = FVector::Up * 300.0f;
	FVector ZombieJumpPower = FVector::Up * 75.0f;
	FVector JumpVector = FVector::Zero;


	FVector HeavyMachineGun_RightArr[5] = { {70,-7},{70,-4},{1,0},{70,4},{70,7} };
	FVector HeavyMachineGun_LeftArr[5] = { {-70,-7},{-70,-4},{-1,0},{-70,4},{-70,7} };
	FVector HeavyMachineGun_UpArr[5] = { {-7,-70},{-4,-70},{0,-1},{4,-70},{7,-70} };
	FVector HeavyMachineGun_DownArr[5] = { {-7,70},{-4,70},{0,1},{4,70},{7,70} };

	FVector VomitProjectileVectorArr[100] = { {48,35},{48,35},{70,41},{70,41},{82,34},
												{82,34},{87,30},{87,30},{79,19} ,{79,19} ,
												{82,14} ,{82,14} ,{1,0},{1,0},
												{65,-13},{65,-13},{43,-16},{43,-16},{52,-21},
												{52,-21}, {43,-20},{42,-20},{39,-27},{39,-27},
												{40,-33},{40,-33},{41,-37},{41,-37},{37,-40},
												{37,-40},{37,-45},{37,-45}, {25,-55}, {25,-55},
												{16,-66},{16,-66} };

	FVector DefaultCollisionScale = { 50,100 };
	FVector DefaultCollisionPosition = { 0, -50 };
	FVector CrouchCollisionScale = { 50,50 };
	FVector CrouchCollisionPosition = { 0,-25 };

	int KnifeDamage = 2;

	FVector KnifeReachCollisionScale = { 70,80 };
	FVector KnifeReachCollisionPosition_Right = {35,-50 };
	FVector KnifeReachCollisionPosition_Left = { -35,-50 };

	FVector CrouchKnifeReachCollisionScale = { 70,40 };
	FVector CrouchKnifeReachCollisionPosition_Right = { 35,-25 };
	FVector CrouchKnifeReachCollisionPosition_Left = { -35,-25 };

	std::vector<UImageRenderer*> VomitRenderer;
	float AccDeltaTime = 0.0f;
	void CameraUpdate(float _DeltaTime);

	float AccInAir = 0.0f;
	float InAirTime = 0.2f;

	bool IsAutoMove = false;
	void AutoMove(float _DeltaTime);
};

