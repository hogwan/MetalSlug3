#pragma once
#include "ExplosionEffect.h"
class ZombieThunder : public AExplosionEffect
{
public:
	// constructor destructor
	ZombieThunder();
	~ZombieThunder();

	// delete Function
	ZombieThunder(const ZombieThunder& _Other) = delete;
	ZombieThunder(ZombieThunder&& _Other) noexcept = delete;
	ZombieThunder& operator=(const ZombieThunder& _Other) = delete;
	ZombieThunder& operator=(ZombieThunder&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

