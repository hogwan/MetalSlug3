#pragma once
#include "ExplosionEffect.h"
class AHugeExplosionEffect : public AExplosionEffect
{
public:
	// constructor destructor
	AHugeExplosionEffect();
	~AHugeExplosionEffect();

	// delete Function
	AHugeExplosionEffect(const AHugeExplosionEffect& _Other) = delete;
	AHugeExplosionEffect(AHugeExplosionEffect&& _Other) noexcept = delete;
	AHugeExplosionEffect& operator=(const AHugeExplosionEffect& _Other) = delete;
	AHugeExplosionEffect& operator=(AHugeExplosionEffect&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
};

