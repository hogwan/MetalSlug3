#pragma once
#include "Enemy.h"

enum class UFOState
{
	None,
	Idle,
	Charging,
	Firing,
};

class MonoEye_UFO : public AEnemy
{
public:
	// constructor destructor
	MonoEye_UFO();
	~MonoEye_UFO();

	// delete Function
	MonoEye_UFO(const MonoEye_UFO& _Other) = delete;
	MonoEye_UFO(MonoEye_UFO&& _Other) noexcept = delete;
	MonoEye_UFO& operator=(const MonoEye_UFO& _Other) = delete;
	MonoEye_UFO& operator=(MonoEye_UFO&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UFOState CurState = UFOState::None;

	void StateUpdate(float _DeltaTime);
	void StateChange(UFOState _State);

	void None(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Charging(float _DeltaTime);
	void Firing(float _DeltaTime);
	
	void IdleStart();
	void ChargingStart();
	void FiringStart();

	UImageRenderer* Body = nullptr;
	UImageRenderer* BrokenBackBody = nullptr;
	UImageRenderer* AncientCharactor = nullptr;

	float CoolTime = 3.0f;
	float AccCoolTime = 0.0f;

	float FiringTime = 3.0f;
	float AccFiring= 0.0f;

	float CharactorMaxSize = 800.f;
	int MaxYPosition = 700;
};

