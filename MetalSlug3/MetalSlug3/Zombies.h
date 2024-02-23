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

	void SetCurState(EnemyZombieState _State)
	{
		CurState = _State;
	}

	virtual void StateChange(EnemyZombieState _State);
	EActorDir DirState = EActorDir::Left;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime)	override;

	EnemyZombieState CurState = EnemyZombieState::None;
	virtual void StateUpdate(float _DeltaTime);

	virtual void None(float _DeltaTime);
	virtual void Lying(float _DeltaTime);
	virtual void Idle(float _DeltaTime);
	virtual void Move(float _DeltaTime);
	virtual void Turn(float _DeltaTime);
	virtual void Stun(float _DeltaTime);
	virtual void Attack(float _DeltaTime, int _LaunchFrame, int _LaunchEffectFrame);
	virtual void Death(float _DeltaTime);

	virtual void NoneStart();
	virtual void LyingStart();
	virtual void IdleStart();
	virtual void MoveStart();
	virtual void TurnStart();
	virtual void StunStart();
	virtual void AttackStart();
	virtual void DeathStart();

	std::string CurAnimName = "None";

	void DirCheck(std::string& _Name);

	FVector GravityVector = FVector::Zero;
	FVector Gravity = FVector::Down * 1300.0f;

	bool WatchPlayer();
	void GravityCheck(float _DeltaTime);
	void GroundUp();

	float Range = 200.0f;
	float MaxStunGauge = 100.0f;
	float CurStunGauge = 0.0f;
	float MoveSpeed = 50.0f;

	int PrevFrame = -1;
	int LaunchFrame = 9;
	int LaunchEffectFrame = 9;

	FVector ProjectileScale = { 400,400 };
	FVector LaunchEffectScale = { 400,400 };
	FVector ProjectileSpawnOffset_Right = { 50,0 };
	FVector ProjectileSpawnOffset_Left = { -50,0 };
	FVector ProjectileSpawnOffset_Height = { 0,-110 };
	FVector LaunchEffectOffset_Up = { 0, -110 };
	FVector LaunchEffectOffset_Right = { 20,0 };
	FVector LaunchEffectoffset_Left = { -20,0 };

	UImageRenderer* LaunchRenderer = nullptr;
	UCollision* DetectCollider = nullptr;


};

