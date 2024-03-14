#pragma once
#include "Enemy.h"

enum class UFOState
{
	None,
	Idle,
	Charging,
	Firing,
	Destroyed,
};

class AMonoEye_UFO : public AEnemy
{
public:
	// constructor destructor
	AMonoEye_UFO();
	~AMonoEye_UFO();

	// delete Function
	AMonoEye_UFO(const AMonoEye_UFO& _Other) = delete;
	AMonoEye_UFO(AMonoEye_UFO&& _Other) noexcept = delete;
	AMonoEye_UFO& operator=(const AMonoEye_UFO& _Other) = delete;
	AMonoEye_UFO& operator=(AMonoEye_UFO&& _Other) = delete;

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
	void Destroyed(float _DeltaTime);
	
	void IdleStart();
	void ChargingStart();
	void FiringStart();
	void DestroyedStart();

	UImageRenderer* Body = nullptr;
	UImageRenderer* BrokenBackBody = nullptr;
	UImageRenderer* AncientCharactor = nullptr;

	float CoolTime = 3.0f;
	float AccCoolTime = 0.0f;

	float FiringTime = 3.0f;
	float AccFiring= 0.0f;

	float CharactorMaxSize = 800.f;
	int MaxYPosition = 700;

	bool Trigger = false;
};

