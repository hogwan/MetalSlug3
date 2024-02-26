#pragma once
#include "Enemy.h"
class AHelicopter : public AEnemy
{
public:
	// constructor destructor
	AHelicopter();
	~AHelicopter();

	// delete Function
	AHelicopter(const AHelicopter& _Other) = delete;
	AHelicopter(AHelicopter&& _Other) noexcept = delete;
	AHelicopter& operator=(const AHelicopter& _Other) = delete;
	AHelicopter& operator=(AHelicopter&& _Other) = delete;

	void StateChange(HelicopterState _State);
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);
	void None(float _DeltaTime);
	void Move(float _DeltaTime);
	void Aiming(float _DeltaTime);

	void NoneStart();
	void MoveStart();
	void AimingStart();

private:
	HelicopterState CurState = HelicopterState::None;
	std::string CurAnimName = "None";

	FVector MoveVector = FVector::Zero;
	void DirCheck();
	float Speed = 300.0f;
};

