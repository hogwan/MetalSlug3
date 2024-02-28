#pragma once
#include "ExplosionEffect.h"
class ABombExplosionEffect : public AExplosionEffect
{
public:
	// constructor destructor
	ABombExplosionEffect();
	~ABombExplosionEffect();

	// delete Function
	ABombExplosionEffect(const ABombExplosionEffect& _Other) = delete;
	ABombExplosionEffect(ABombExplosionEffect&& _Other) noexcept = delete;
	ABombExplosionEffect& operator=(const ABombExplosionEffect& _Other) = delete;
	ABombExplosionEffect& operator=(ABombExplosionEffect&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

