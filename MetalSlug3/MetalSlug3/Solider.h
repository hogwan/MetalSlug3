#pragma once
#include "Enemy.h"
#include "ContentsHelper.h"

class ASolider : public AEnemy
{
public:
	// constrcuter destructer
	ASolider();
	~ASolider();

	// delete Function
	ASolider(const ASolider& _Other) = delete;
	ASolider(ASolider&& _Other) noexcept = delete;
	ASolider& operator=(const ASolider& _Other) = delete;
	ASolider& operator=(ASolider&& _Other) noexcept = delete;

	FVector TargetVector = FVector::Zero;
	FVector MoveVector = FVector::Zero;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UCollision* KnifeAttackCollider = nullptr;

	void StateUpdate(float _DeltaTime);
	void StateChange(SoilderState _State);

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

	SoliderPattern Pattern = SoliderPattern::KnifeAttack;
	std::string CurAnimName = "None";
	void TargetCheck();
	void DirCheck();
	void GravityCheck(float _DeltaTime);
	void GroundUp();

	void ChangePattern(SoliderPattern _Pattern);
	SoilderState CurState = SoilderState::None;

	FVector KnifeReachCollisionScale = { 30,80 };
	FVector KnifeReachCollisionPosition_Right = { 35,-50 };
	FVector KnifeReachCollisionPosition_Left = { -35,-50 };
};

