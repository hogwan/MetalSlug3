#pragma once
#include "Helicopter.h"
class ALeaderHelicopter : public AHelicopter
{
public:
	// constructor destructor
	ALeaderHelicopter();
	~ALeaderHelicopter();

	// delete Function
	ALeaderHelicopter(const ALeaderHelicopter& _Other) = delete;
	ALeaderHelicopter(ALeaderHelicopter&& _Other) noexcept = delete;
	ALeaderHelicopter& operator=(const ALeaderHelicopter& _Other) = delete;
	ALeaderHelicopter& operator=(ALeaderHelicopter&& _Other) = delete;

	static std::list<AHelicopter*> HeliList;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Shoot(float _DeltaTime) override;
	void ShootStart() override;

	void Move(float _DeltaTime) override;
	void MoveStart() override;

	float AccAttack = 0.0f;
	float AttackCoolTime = 3.0f;
};

