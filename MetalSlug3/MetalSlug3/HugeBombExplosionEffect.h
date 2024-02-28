#pragma once
#include "ExplosionEffect.h"
class AHugeBombExplosionEffect : public AExplosionEffect
{
public:
	// constructor destructor
	AHugeBombExplosionEffect();
	~AHugeBombExplosionEffect();

	// delete Function
	AHugeBombExplosionEffect(const AHugeBombExplosionEffect& _Other) = delete;
	AHugeBombExplosionEffect(AHugeBombExplosionEffect&& _Other) noexcept = delete;
	AHugeBombExplosionEffect& operator=(const AHugeBombExplosionEffect& _Other) = delete;
	AHugeBombExplosionEffect& operator=(AHugeBombExplosionEffect&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

