#pragma once
#include "Enemy.h"
#include "ContentsHelper.h"

class ASoldier : public AEnemy
{
public:
	// constrcuter destructer
	ASoldier();
	~ASoldier();

	// delete Function
	ASoldier(const ASoldier& _Other) = delete;
	ASoldier(ASoldier&& _Other) noexcept = delete;
	ASoldier& operator=(const ASoldier& _Other) = delete;
	ASoldier& operator=(ASoldier&& _Other) noexcept = delete;

	FVector TargetVector = FVector::Zero;
	FVector MoveVector = FVector::Right;
	float RunAwayRange = 300.0f;
	float ThrowRange = 200.0f;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UCollision* KnifeAttackCollider = nullptr;

	void StateUpdate(float _DeltaTime);
	void StateChange(SoldierState _State);

	void None(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);
	void Throw(float _DeltaTime);
	void KnifeAttack(float _DeltaTime);
	void Death(float _DeltaTime);

	void NoneStart();
	void IdleStart();
	void MoveStart();
	void ThrowStart();
	void KnifeAttackStart();
	void DeathStart();

	SoldierPattern Pattern = SoldierPattern::KnifeAttack;
	std::string CurAnimName = "None";
	void DirCheck();
	void GravityCheck(float _DeltaTime);
	void GroundUp();
	void RandomPattern();

	void ChangePattern(SoldierPattern _Pattern);
	SoldierState CurState = SoldierState::None;

	FVector KnifeReachCollisionScale = { 30,80 };
	FVector KnifeReachCollisionPosition_Right = { 35,-50 };
	FVector KnifeReachCollisionPosition_Left = { -35,-50 };

	FVector BombSpawnOffset_Right = { 75,0 };
	FVector BombSpawnOffset_Left = { -75,0 };

	float MoveSpeed = 150.0f;

	int PrevFrame = -1;
};

