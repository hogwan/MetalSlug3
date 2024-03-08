#pragma once
#include "ExplosionEffect.h"
class AVomitExplosionEffect : public AExplosionEffect
{
public:
	// constructor destructor
	AVomitExplosionEffect();
	~AVomitExplosionEffect();

	// delete Function
	AVomitExplosionEffect(const AVomitExplosionEffect& _Other) = delete;
	AVomitExplosionEffect(AVomitExplosionEffect&& _Other) noexcept = delete;
	AVomitExplosionEffect& operator=(const AVomitExplosionEffect& _Other) = delete;
	AVomitExplosionEffect& operator=(AVomitExplosionEffect&& _Other) = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime);


};

