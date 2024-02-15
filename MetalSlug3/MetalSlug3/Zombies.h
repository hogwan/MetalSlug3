#pragma once
#include "Enemy.h"
class AZombies : public AEnemy
{
public:
	// constructor destructor
	AZombies();
	~AZombies();

	// delete Function
	AZombies(const AZombies& _Other) = delete;
	AZombies(AZombies&& _Other) noexcept = delete;
	AZombies& operator=(const AZombies& _Other) = delete;
	AZombies& operator=(AZombies&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime)	override;

	EActorDir DirState = EActorDir::Left;
	EnemyZombieState CurState = EnemyZombieState::None;
	void StateUpdate(float _DeltaTime);
	void StateChange(EnemyZombieState _State);

	void None(float _DeltaTime);
	void Lying(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Turn(float _DeltaTime);
	void Stun(float _DeltaTime);
	void Attack(float _DeltaTime, int _LaunchFrame);

	void NoneStart();
	void LyingStart();
	void IdleStart();
	void MoveStart();
	void TurnStart();
	void StunStart();
	void AttackStart();

	std::string CurAnimName = "None";

	void DirCheck(std::string& _Name);

	FVector GravityVector = FVector::Zero;
	FVector Gravity = FVector::Down * 1300.0f;

	bool PlayerInRange();
	bool WatchPlayer();
	void GravityCheck(float _DeltaTime);
	void GroundUp();

	float Range = 300.0f;
	float MaxStunGauge = 100.0f;
	float CurStunGauge = 0.0f;
	float CoolTime = 1.0f;
	float AccTime = 0.0f;
	float MoveSpeed = 50.0f;

	int PrevFrame = -1;
	int LaunchFrame = 9;

	FVector ProjectileScale = { 400,400 };
	FVector LaunchEffectScale = { 400,400 };
	FVector ProjectileSpawnOffset_Right = { 50,0 };
	FVector ProjectileSpawnOffset_Left = { -50,0 };
	FVector ProjectileSpawnOffset_Height = { 0,-110 };
	FVector LaunchEffectOffset_Up = { 0, -110 };
	FVector LaunchEffectOffset_Right = { 20,0 };
	FVector LaunchEffectoffset_Left = { -20,0 };

	UImageRenderer* LaunchRenderer = nullptr;
};

