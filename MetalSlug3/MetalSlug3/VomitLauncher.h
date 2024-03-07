#pragma once
#include "MT3Object.h"

class AVomitLauncher : public AMT3Object
{
public:
	// constructor destructor
	AVomitLauncher();
	~AVomitLauncher();

	// delete Function
	AVomitLauncher(const AVomitLauncher& _Other) = delete;
	AVomitLauncher(AVomitLauncher&& _Other) noexcept = delete;
	AVomitLauncher& operator=(const AVomitLauncher& _Other) = delete;
	AVomitLauncher& operator=(AVomitLauncher&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UImageRenderer* Renderer = nullptr;

	std::vector<class AZombieVomitProjectile*> VomitProjectiles;

	FVector ShootVector = FVector::Zero;
	FVector InitialShootVector = FVector::Zero;
	FVector LastShootVector = FVector::Zero;

	FVector InitialPosition = FVector::Zero;
	FVector InitialVelocity = FVector::Zero;

	float ShootPower = 100.0f;
	float gravity = 1000.f;

	float AccTime = 0.0f;
	float CoolTime = 0.05f;

	void LaunchLogic();
	void DamageLogic();
};

