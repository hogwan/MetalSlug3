#pragma once
#include <EngineCore/Actor.h>
#include "ContentsHelper.h"
#include "Enemy.h"
class AManZombie1 : public AEnemy
{
public:
	// constrcuter destructer
	AManZombie1();
	~AManZombie1();

	// delete Function
	AManZombie1(const AManZombie1& _Other) = delete;
	AManZombie1(AManZombie1&& _Other) noexcept = delete;
	AManZombie1& operator=(const AManZombie1& _Other) = delete;
	AManZombie1& operator=(AManZombie1&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime)	override;

	EActorDir DirState = EActorDir::Left;
	EnemyZombieState CurState = EnemyZombieState::None;
	void StateUpdate(float _DeltaTime);
	void StateChange(EnemyZombieState _State);

	/*None,
		Lying,
		Idle,
		Move,
		Turn,
		Stun,
		Attack,*/

	void None(float _DeltaTime);
	void Lying(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Turn(float _DeltaTime);
	void Stun(float _DeltaTime);
	void Attack(float _DeltaTime);

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
	float MoveSpeed = 200.0f;
};
