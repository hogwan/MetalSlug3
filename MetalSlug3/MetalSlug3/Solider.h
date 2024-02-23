#pragma once
#include "Enemy.h"
#include "ContentsHelper.h"

enum class SoliderPattern
{
	KnifeAttack,
	Throw,
	RunAway,
};

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

	template<typename EnumType>
	void ChangePattern(EnumType _Order = 0)
	{
		return CreateCollision(static_cast<int>(_Order));
	}
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

	int Pattern = 0;
	std::string CurAnimName = "None";
	void TargetCheck();
	void DirCheck();
	void GravityCheck(float _DeltaTime);
	void GroundUp();

	void ChangePattern(int _Pattern);
	SoilderState CurState = SoilderState::None;

	FVector KnifeReachCollisionScale = { 30,80 };
	FVector KnifeReachCollisionPosition_Right = { 35,-50 };
	FVector KnifeReachCollisionPosition_Left = { -35,-50 };
};

