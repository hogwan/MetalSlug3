#pragma once
#include "ExplosionEffect.h"
class RocketLauncher_LaunchEffect : public AExplosionEffect
{
public:
	// constructor destructor
	RocketLauncher_LaunchEffect();
	~RocketLauncher_LaunchEffect();

	// delete Function
	RocketLauncher_LaunchEffect(const RocketLauncher_LaunchEffect& _Other) = delete;
	RocketLauncher_LaunchEffect(RocketLauncher_LaunchEffect&& _Other) noexcept = delete;
	RocketLauncher_LaunchEffect& operator=(const RocketLauncher_LaunchEffect& _Other) = delete;
	RocketLauncher_LaunchEffect& operator=(RocketLauncher_LaunchEffect&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	FVector Dir = FVector::Zero;
};

