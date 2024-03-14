#pragma once
#include "Enemy.h"
#include <EnginePlatform/EngineSound.h>
class AEliteHelicopter : public AEnemy
{
public:
	// constructor destructor
	AEliteHelicopter();
	~AEliteHelicopter();

	// delete Function
	AEliteHelicopter(const AEliteHelicopter& _Other) = delete;
	AEliteHelicopter(AEliteHelicopter&& _Other) noexcept = delete;
	AEliteHelicopter& operator=(const AEliteHelicopter& _Other) = delete;
	AEliteHelicopter& operator=(AEliteHelicopter&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Propeller = nullptr;


	float Speed = 0.0f;
	float TargetY = 1860.0f;

	float ShootCoolTime = 2.5f;
	float AccShootTime = 0.0f;

	float LaunchCoolTime = 0.3f;
	float AccLaunchTime = 0.0f;

	bool IsShooting = false;
	int Bullet = 3;

	UEngineSoundPlayer PropellerSound;
};

