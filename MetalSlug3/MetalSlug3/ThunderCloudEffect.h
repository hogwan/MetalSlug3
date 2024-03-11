#pragma once
#include "ExplosionEffect.h"
class ThunderCloudEffect : public AExplosionEffect
{
public:
	// constructor destructor
	ThunderCloudEffect();
	~ThunderCloudEffect();

	// delete Function
	ThunderCloudEffect(const ThunderCloudEffect& _Other) = delete;
	ThunderCloudEffect(ThunderCloudEffect&& _Other) noexcept = delete;
	ThunderCloudEffect& operator=(const ThunderCloudEffect& _Other) = delete;
	ThunderCloudEffect& operator=(ThunderCloudEffect&& _Other) = delete;

	int ThunderSize = 0;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};

